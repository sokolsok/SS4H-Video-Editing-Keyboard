/*
 * knob.c
 *
 * Created by: Smart Solutions for Home - Sebastian Sokołowski
 *
 */

#include "knob.h"

extern Status_t Status;
extern HID_Status_t HID_Status;

RDY_Key_t KnobMacro[21] =
{
		{MOD_None, 0,KEY_None},								//0 - No key pressed
		{MOD_None, 0, KEY_Left},							//1 - Turn (tick) Left
		{MOD_None, 0, KEY_Right},							//2 - Turn (tick) Right
		{MOD_SHIFT_L, 0, KEY_Left},							//3 - Turn (tick) Left + Shift
		{MOD_SHIFT_L, 0, KEY_Right},						//4 - Turn (tick) Right + Shift
		{MOD_CTRL_L | MOD_ALT_L, 0, KEY_Minus},				//5 - Turn (tick) Left + Decrease audio +1
		{MOD_CTRL_L | MOD_ALT_L, 0, KEY_Equals},			//6 - Turn (tick) Left + Increase audio +1
		{MOD_CTRL_L, 0, KEY_Minus},							//7 - Turn (tick) Left + Zoom IN
		{MOD_CTRL_L, 0, KEY_Equals},						//8 - Turn (tick) Left + Zoom OUT
		{MOD_None, 0, KEY_Up},								//9 - Turn (tick) Left + Begin Clip
		{MOD_None, 0, KEY_Down},							//10 - Turn (tick) Left + End Clip
		{MOD_None, 0, KEY_Comma},							//11 - Turn (tick)
		{MOD_None, 0, KEY_Period},							//12 - Turn (tick)
		{MOD_CTRL_L | MOD_SHIFT_L, 0, KEY_Comma},			//13 - Turn (tick) Swap left
		{MOD_CTRL_L | MOD_SHIFT_L, 0, KEY_Period},			//14 - Turn (tick) Swap right
		{MOD_SHIFT_L, 0, KEY_Comma},						//15 - Turn (tick)
		{MOD_SHIFT_L, 0, KEY_Period},						//16 - Turn (tick)

		/* Shuttle mode */
		{MOD_None, 0, KEY_J},								//11 - Turn (tick) 17
		{MOD_None, 0, KEY_L},								//12 - Turn (tick) 18
		{MOD_None, 0, KEY_K},								//15 - Turn (tick) 19
		{MOD_SHIFT_L, 0, KEY_K}								//16 - Turn (tick) 20
};

void Shuttle_mode_Routine(void);

void LEDS_Toggle(uint8_t state)
{
	static uint8_t knob_flag;

	if(state)
	{
		if(knob_flag == 0)
		{
			  HAL_GPIO_WritePin(LEDS_A_GPIO_Port, LEDS_A_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(LEDS_B_GPIO_Port, LEDS_B_Pin, GPIO_PIN_RESET);

			  knob_flag = 1;
		}
		else
		{
			  HAL_GPIO_WritePin(LEDS_A_GPIO_Port, LEDS_A_Pin, GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(LEDS_B_GPIO_Port, LEDS_B_Pin, GPIO_PIN_SET);

			  knob_flag = 0;
		}
	}
	else
	{
		  HAL_GPIO_WritePin(LEDS_A_GPIO_Port, LEDS_A_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(LEDS_B_GPIO_Port, LEDS_B_Pin, GPIO_PIN_SET);
	}
}

void KnobRoutine(void)
{
	static uint8_t KnobLED_counter;

	Status.KnobCounetr = htim2.Instance->CNT;

	/* Knob rotated right */
	if(Status.KnobCounetr >= KNOB_DIV)
	{
		Status.KnobDir = 1;
		htim2.Instance->CNT = 0;

		LEDS_Toggle(1);
		KnobLED_counter = 0;

		Status.Knob_Speed = Status.Knob_Speed_counter;
		Status.Knob_Speed_counter = 0;

		if(Status.Edit_mode == NONE_MODE)
		{
			if(Status.Knob_Mode == JOG)
				Status.KonbRotated = 1;
			else if(Status.Knob_Mode == SCRL)
				Status.KonbRotated = 3;
			else if(Status.Knob_Mode == SHTL)
				Shuttle_mode_Routine();
		}
		else if((Status.Edit_mode == SLIP) || (Status.Edit_mode == SLIDE))
		{
			if(Status.Knob_Mode == JOG)
				Status.KonbRotated = 11;
			else if(Status.Knob_Mode == SCRL)
				Status.KonbRotated = 15;
		}
		else if((Status.Edit_mode == ZOOM))
			Status.KonbRotated = 7;
		else if((Status.Edit_mode == AUDIO))
			Status.KonbRotated = 5;
		else if((Status.Edit_mode == SWAP))
			Status.KonbRotated = 13;
		else if((Status.Edit_mode == SNAP) || (Status.Edit_mode == SLIDE))
			Status.KonbRotated = 9;
	}
	/* Knob rotated left */
	else if(Status.KnobCounetr < -KNOB_DIV)
	{
		Status.KnobDir = 0;
		htim2.Instance->CNT = 0;

		LEDS_Toggle(1);
		KnobLED_counter = 0;

		Status.Knob_Speed = Status.Knob_Speed_counter;
		Status.Knob_Speed_counter = 0;

		if(Status.Edit_mode == NONE_MODE)
		{
			if(Status.Knob_Mode == JOG)
				Status.KonbRotated = 1;
			else if(Status.Knob_Mode == SCRL)
				Status.KonbRotated = 3;
			else if(Status.Knob_Mode == SHTL)
				Shuttle_mode_Routine();
		}
		else if((Status.Edit_mode == SLIP) || (Status.Edit_mode == SLIDE))
		{
			if(Status.Knob_Mode == JOG)
				Status.KonbRotated = 11;
			else if(Status.Knob_Mode == SCRL)
				Status.KonbRotated = 15;
		}
		else if((Status.Edit_mode == ZOOM))
			Status.KonbRotated = 7;
		else if((Status.Edit_mode == AUDIO))
			Status.KonbRotated = 5;
		else if((Status.Edit_mode == SWAP))
			Status.KonbRotated = 13;
		else if((Status.Edit_mode == SNAP) || (Status.Edit_mode == SLIDE))
			Status.KonbRotated = 9;
	}
	else
	{
		if(KnobLED_counter < 40)
			KnobLED_counter++;
		else
			LEDS_Toggle(0);

	}

	if(Status.KonbRotated)
	{
		HID_Status.buff[0] = KnobMacro[Status.KonbRotated + Status.KnobDir];

		HID_Status.buff_ready = SET;

		Status.KonbRotated = 0;
	}
}

void Shuttle_mode_Routine(void)
{
	if(Status.KnobDir == 1) /* Right */
	{
		switch(Status.Shuttle_mode)
		{
			case SHTL_STOP:
				Status.Shuttle_mode = FORW_1;
				Status.KonbRotated = 17;
			break;
			case FORW_1:
				Status.Shuttle_mode = FORW_2;
				Status.KonbRotated = 17;
			break;
			case FORW_2:
				Status.Shuttle_mode = FORW_4;
				Status.KonbRotated = 17;
			break;
			case FORW_4:
				Status.Shuttle_mode = FORW_8;
				Status.KonbRotated = 17;
			break;
			case FORW_8:
				Status.Shuttle_mode = FORW_16;
				Status.KonbRotated = 17;
			break;
			case FORW_16:
				Status.Shuttle_mode = FORW_32;
				Status.KonbRotated = 17;
			break;
			case FORW_32:
				Status.Shuttle_mode = FORW_64;
				Status.KonbRotated = 17;
			break;
			case REW_1:
				Status.Shuttle_mode = SHTL_STOP;
				Status.KonbRotated = 14;
			break;
			case REW_2:
				Status.Shuttle_mode = REW_1;
				Status.KonbRotated = 19;
			break;
			case REW_4:
				Status.Shuttle_mode = REW_2;
				Status.KonbRotated = 19;
			break;
			case REW_8:
				Status.Shuttle_mode = REW_4;
				Status.KonbRotated = 19;
			break;
			case REW_16:
				Status.Shuttle_mode = REW_8;
				Status.KonbRotated = 19;
			break;
			case REW_32:
				Status.Shuttle_mode = REW_16;
				Status.KonbRotated = 19;
			break;
			case REW_64:
				Status.Shuttle_mode = REW_32;
				Status.KonbRotated = 19;
			break;
		}
	}
	else if(Status.KnobDir == 0) /* Left */
	{
		switch(Status.Shuttle_mode)
		{
			case SHTL_STOP:
				Status.Shuttle_mode = REW_1;
				Status.KonbRotated = 17;
			break;
			case REW_1:
				Status.Shuttle_mode = REW_2;
				Status.KonbRotated = 17;
			break;
			case REW_2:
				Status.Shuttle_mode = REW_4;
				Status.KonbRotated = 17;
			break;
			case REW_4:
				Status.Shuttle_mode = REW_8;
				Status.KonbRotated = 17;
			break;
			case REW_8:
				Status.Shuttle_mode = REW_16;
				Status.KonbRotated = 17;
			break;
			case REW_16:
				Status.Shuttle_mode = REW_32;
				Status.KonbRotated = 17;
			break;
			case REW_32:
				Status.Shuttle_mode = REW_64;
				Status.KonbRotated = 17;
			break;
			case FORW_1:
				Status.Shuttle_mode = SHTL_STOP;
				Status.KonbRotated = 19;
			break;
			case FORW_2:
				Status.Shuttle_mode = FORW_1;
				Status.KonbRotated = 20;
			break;
			case FORW_4:
				Status.Shuttle_mode = FORW_2;
				Status.KonbRotated = 20;
			break;
			case FORW_8:
				Status.Shuttle_mode = FORW_4;
				Status.KonbRotated = 20;
			break;
			case FORW_16:
				Status.Shuttle_mode = FORW_8;
				Status.KonbRotated = 20;
			break;
			case FORW_32:
				Status.Shuttle_mode = FORW_16;
				Status.KonbRotated = 20;
			break;
			case FORW_64:
				Status.Shuttle_mode = FORW_32;
				Status.KonbRotated = 20;
			break;
		}
	}
}


