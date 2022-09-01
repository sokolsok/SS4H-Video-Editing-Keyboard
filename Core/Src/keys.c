/*
 * keys.c
 *
 * Created by: Smart Solutions for Home - Sebastian Sokołowski
 *
 */

#include "keys.h"

extern Status_t Status;
extern HID_Status_t HID_Status;

/*
 *   @brief Keys map:
 *    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *   +                     _________________                      +
 *   +  1     2    3      |                 |         26   27     +
 *	 +	4     5    6      |       LCD       |                     +
 *	 +	                  |                 |      28   29   25   +
 *	 +	                  |_________________|                     +
 *	 +	   7    8                                      ___        +
 *	 +	9    10   11       18   19   20   21         /     \      +
 *	 +	12   13   14       22   23   24   32        | KNOB  |    +
 *	 +	15   16   17               31                \_____/    +
 *	 +                                                        +
 *	  ++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */
RDY_Key_t KeyMacro[46] =
{
		{MOD_None, 0, KEY_None},							//No key pressed
		{0, 0, 0},											//Key 1 - Escape - Key Sequence 3
		{MOD_SHIFT_L, 0, KEY_F12},							//Key 2 - APPND
		{MOD_SHIFT_L, 0, KEY_F10},							//Key 3 - Ripple overwrite
		{0, 0, 0},											//Key 4 - Smart Insert - Key Sequence 1
		{MOD_None, 0, KEY_F12},								//Key 5 - Place on Top
		{MOD_None, 0, KEY_F10},								//Key 6 - Overwrite
		{MOD_None, 0, KEY_I},								//Key 7 - Mark IN
		{MOD_None, 0, KEY_O},								//Key 8 - Mark OUT
		{MOD_SHIFT_L | MOD_CTRL_L, 0, KEY_LeftBracket},		//Key 9 - Trim IN
		{MOD_SHIFT_L | MOD_CTRL_L, 0, KEY_RightBracket},	//Key 10 - Trim OUT
		{0, 0, 0},											//Key 11 - Transition - Key Sequence 2
		{MOD_None, 0, KEY_F1},								//Key 12 - Slip (custom setting in DV)
		{MOD_None, 0, KEY_F2},								//Key 13 - Slide (custom setting in DV)
		{MOD_None, 0, KEY_Delete},							//Key 14 - Delete
		{MOD_CTRL_L, 0, KEY_Backslash},						//Key 15 - Split Clip
		{MOD_ALT_L, 0, KEY_Backslash},						//Key 16 - Join Clip
		{MOD_None, 0, KEY_DeleteForward},					//Key 17 - Ripple Delete
		{0, 0, 0},				  							//Key 18 - Enable/Disable Clip - Key Sequence 4
		{MOD_None, 0, KEY_None},							//Key 19 - Zoom
		{MOD_None, 0, KEY_None},							//Key 20 - Audio level
		{MOD_None, 0, KEY_P},								//Key 21 - Full view
		{0, 0, 0},											//Key 22 - Speed - Key Sequence 5
		{0, 0, 0},											//Key 23 - Curve - Key Sequence 6
		{MOD_None, 0, KEY_None},							//Key 24 - Snap (for tests)
		{0, 0, 0},											//Key 25 - Knob mode: SCRL
		{MOD_CTRL_L, 0, KEY_3},								//Key 26 - Source viewer
		{MOD_CTRL_L, 0, KEY_4},								//Key 27 - Timeline viewer
		{0, 0, 0},											//Key 28 - Knob mode: SHTL
		{0, 0, 0},											//Key 29 - Knob mode: JOG
		{MOD_None, 0, KEY_None},							//Key 30 - N.A.
		{MOD_None, 0, KEY_Space},							//Key 31 - Play/Stop
		{MOD_None, 0, KEY_None},							//Key 32 - Delete

		/* Smart Insert - Key Sequence 1 */
		{MOD_None, 0, KEY_V},								//33 - Select
		{MOD_None, 0, KEY_F9},								//34 - Insert
		{MOD_CTRL_L | MOD_SHIFT_L, 0, KEY_A},				//35 - Deselect All

		/* Transition - Key Sequence 2 */
		{MOD_None, 0, KEY_V},								//36 - Select
		{MOD_CTRL_L, 0, KEY_T},								//37 - Standard transition + Deselect All

		/* Escape - Key Sequence 3 */
		{MOD_None, 0, KEY_Escape},							//38 - Escape
		{MOD_None, 0, KEY_A},								//39 - Selection mode + Deselect All

		/* Enable/Disable Clip - Key Sequence 4 */
		{MOD_SHIFT_L, 0, KEY_V},							//40 - Select clip
		{MOD_None, 0, KEY_D},								//41 - Enable/Disable Clip + Deselect All

		/* Speed - Key Sequence 5 */
		{MOD_SHIFT_L, 0, KEY_V},							//42 - Select clip
		{MOD_CTRL_L, 0, KEY_R},								//43 - Speed + Deselect All

		/* Curve - Key Sequence 6 */
		{MOD_SHIFT_L, 0, KEY_V},							//44 - Select clip
		{MOD_SHIFT_L, 0, KEY_C},							//45 - Curve + Deselect All
};

/* GPIO EXTI Callback */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//HAL_GPIO_WritePin(TEST_POINT_GPIO_Port, TEST_POINT_Pin, GPIO_PIN_SET);

	/* set debouncing time to defined value */
	__HAL_TIM_SET_PRESCALER(&htim7, (100-(100-DEBOUNCING_TIME))-1);

	switch(GPIO_Pin)
	{
		case ROW1_Pin:
			if(Status.Rows.ROW1 == IDLE)
				Status.Rows.ROW1 = DEBOUNCED;

			HAL_TIM_Base_Start_IT(&htim7);
			break;
		case ROW2_Pin:
			if(Status.Rows.ROW2 == IDLE)
				Status.Rows.ROW2 = DEBOUNCED;

			HAL_TIM_Base_Start_IT(&htim7);
			break;
		case ROW3_Pin:
			if(Status.Rows.ROW3 == IDLE)
				Status.Rows.ROW3 = DEBOUNCED;

			HAL_TIM_Base_Start_IT(&htim7);
			break;
		case ROW4_Pin:
			if(Status.Rows.ROW4 == IDLE)
				Status.Rows.ROW4 = DEBOUNCED;

			HAL_TIM_Base_Start_IT(&htim7);
			break;
		case ROW5_Pin:
			if(Status.Rows.ROW5 == IDLE)
				Status.Rows.ROW5 = DEBOUNCED;

			HAL_TIM_Base_Start_IT(&htim7);
			break;
		case ROW6_Pin:
			if(Status.Rows.ROW6 == IDLE)
				Status.Rows.ROW6 = DEBOUNCED;

			HAL_TIM_Base_Start_IT(&htim7);
			break;
	}
}

/* DEBOUNCING */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim7)
	{
		HAL_TIM_Base_Stop_IT(&htim7);

		if(Status.Rows.ROW1 == DEBOUNCED)
		{
			if(HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin) == GPIO_PIN_RESET)
			{
				Status.Rows.ROW1 = PRESSED;
				Status.Scan_Rows = 1;
			}
			else
				Status.Rows.ROW1 = IDLE;
		}
		else if(Status.Rows.ROW2 == DEBOUNCED)
		{
			if(HAL_GPIO_ReadPin(ROW2_GPIO_Port, ROW2_Pin) == GPIO_PIN_RESET)
			{
				Status.Rows.ROW2 = PRESSED;
				Status.Scan_Rows = 2;
			}
			else
				Status.Rows.ROW2 = IDLE;
		}
		else if(Status.Rows.ROW3 == DEBOUNCED)
		{
			if(HAL_GPIO_ReadPin(ROW3_GPIO_Port, ROW3_Pin) == GPIO_PIN_RESET)
			{
				Status.Rows.ROW3 = PRESSED;
				Status.Scan_Rows = 3;
			}
			else
				Status.Rows.ROW3 = IDLE;
		}
		else if(Status.Rows.ROW4 == DEBOUNCED)
		{
			if(HAL_GPIO_ReadPin(ROW4_GPIO_Port, ROW4_Pin) == GPIO_PIN_RESET)
			{
				Status.Rows.ROW4 = PRESSED;
				Status.Scan_Rows = 4;
			}
			else
				Status.Rows.ROW4 = IDLE;
		}
		else if(Status.Rows.ROW5 == DEBOUNCED)
		{
			if(HAL_GPIO_ReadPin(ROW5_GPIO_Port, ROW5_Pin) == GPIO_PIN_RESET)
			{
				Status.Rows.ROW5 = PRESSED;
				Status.Scan_Rows = 5;
			}
			else
				Status.Rows.ROW5 = IDLE;
		}
		else if(Status.Rows.ROW6 == DEBOUNCED)
		{
			if(HAL_GPIO_ReadPin(ROW6_GPIO_Port, ROW6_Pin) == GPIO_PIN_RESET)
			{
				Status.Rows.ROW6 = PRESSED;
				Status.Scan_Rows = 6;
			}
			else
				Status.Rows.ROW6 = IDLE;
		}

		Scan_Routine(Status.Scan_Rows);
	}
}

void Set_Col_LOW(uint8_t col)
{
	switch(col)
	{
		case 0:
			HAL_GPIO_WritePin(COL1_GPIO_Port, COL1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(COL2_GPIO_Port, COL2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(COL3_GPIO_Port, COL3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(COL4_GPIO_Port, COL4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(COL5_GPIO_Port, COL5_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(COL6_GPIO_Port, COL6_Pin, GPIO_PIN_RESET);
		break;
		case 1:
			HAL_GPIO_WritePin(COL1_GPIO_Port, COL1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(COL2_GPIO_Port, COL2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL3_GPIO_Port, COL3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL4_GPIO_Port, COL4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL5_GPIO_Port, COL5_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL6_GPIO_Port, COL6_Pin, GPIO_PIN_SET);
		break;
		case 2:
			HAL_GPIO_WritePin(COL1_GPIO_Port, COL1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL2_GPIO_Port, COL2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(COL3_GPIO_Port, COL3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL4_GPIO_Port, COL4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL5_GPIO_Port, COL5_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL6_GPIO_Port, COL6_Pin, GPIO_PIN_SET);
		break;
		case 3:
			HAL_GPIO_WritePin(COL1_GPIO_Port, COL1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL2_GPIO_Port, COL2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL3_GPIO_Port, COL3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(COL4_GPIO_Port, COL4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL5_GPIO_Port, COL5_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL6_GPIO_Port, COL6_Pin, GPIO_PIN_SET);
		break;
		case 4:
			HAL_GPIO_WritePin(COL1_GPIO_Port, COL1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL2_GPIO_Port, COL2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL3_GPIO_Port, COL3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL4_GPIO_Port, COL4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(COL5_GPIO_Port, COL5_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL6_GPIO_Port, COL6_Pin, GPIO_PIN_SET);
		break;
		case 5:
			HAL_GPIO_WritePin(COL1_GPIO_Port, COL1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL2_GPIO_Port, COL2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL3_GPIO_Port, COL3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL4_GPIO_Port, COL4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL5_GPIO_Port, COL5_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(COL6_GPIO_Port, COL6_Pin, GPIO_PIN_SET);
		break;
		case 6:
			HAL_GPIO_WritePin(COL1_GPIO_Port, COL1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL2_GPIO_Port, COL2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL3_GPIO_Port, COL3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL4_GPIO_Port, COL4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL5_GPIO_Port, COL5_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COL6_GPIO_Port, COL6_Pin, GPIO_PIN_RESET);
		break;
	}
}

GPIO_PinState Read_Row(uint8_t row)
{
	switch(row)
	{
		case 1:
			return HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin);
		break;
		case 2:
			return HAL_GPIO_ReadPin(ROW2_GPIO_Port, ROW2_Pin);
		break;
		case 3:
			return HAL_GPIO_ReadPin(ROW3_GPIO_Port, ROW3_Pin);
		break;
		case 4:
			return HAL_GPIO_ReadPin(ROW4_GPIO_Port, ROW4_Pin);
		break;
		case 5:
			return HAL_GPIO_ReadPin(ROW5_GPIO_Port, ROW5_Pin);
		break;
		case 6:
			return HAL_GPIO_ReadPin(ROW6_GPIO_Port, ROW6_Pin);
		break;
	}

	return 2; //Wrong input
}

uint8_t Scan_Routine(uint8_t no)
{
	uint8_t i;

	switch(no)
	{
		case 1:
			for(i = 1; i <= 6; i++)
			{
				Set_Col_LOW(i);

				if(HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin) == GPIO_PIN_RESET)
				{
					return Status.Pressed_Key = i;

				}
			}

			Set_Col_LOW(0);

			Status.Pressed_Key = 0;
			Status.Rows.ROW1 = IDLE;
			Status.Scan_Rows = RESET;
		break;
		case 2:
			for(i = 1; i <= 6; i++)
			{
				Set_Col_LOW(i);

				if(HAL_GPIO_ReadPin(ROW2_GPIO_Port, ROW2_Pin) == GPIO_PIN_RESET)
				{
					return Status.Pressed_Key = i+6;
				}
			}

			Set_Col_LOW(0);

			Status.Pressed_Key = 0;
			Status.Rows.ROW2 = IDLE;
			Status.Scan_Rows = RESET;
		break;
		case 3:
			for(i = 1; i <= 6; i++)
			{
				Set_Col_LOW(i);

				if(HAL_GPIO_ReadPin(ROW3_GPIO_Port, ROW3_Pin) == GPIO_PIN_RESET)
				{
					return Status.Pressed_Key = i+12;
				}
			}

			Set_Col_LOW(0);

			Status.Pressed_Key = 0;
			Status.Rows.ROW3 = IDLE;
			Status.Scan_Rows = RESET;
		break;
		case 4:
			for(i = 1; i <= 6; i++)
			{
				Set_Col_LOW(i);

				if(HAL_GPIO_ReadPin(ROW4_GPIO_Port, ROW4_Pin) == GPIO_PIN_RESET)
				{
					return Status.Pressed_Key = i+18;
				}
			}

			Set_Col_LOW(0);

			Status.Pressed_Key = 0;
			Status.Rows.ROW4 = IDLE;
			Status.Scan_Rows = RESET;
		break;
		case 5:
			for(i = 1; i <= 6; i++)
			{
				Set_Col_LOW(i);

				if(HAL_GPIO_ReadPin(ROW5_GPIO_Port, ROW5_Pin) == GPIO_PIN_RESET)
				{
					return Status.Pressed_Key = i+24;
				}
			}

			Set_Col_LOW(0);

			Status.Pressed_Key = 0;
			Status.Rows.ROW5 = IDLE;
			Status.Scan_Rows = RESET;
		break;
		case 6:
			for(i = 1; i <= 6; i++)
			{
				Set_Col_LOW(i);

				if(HAL_GPIO_ReadPin(ROW6_GPIO_Port, ROW6_Pin) == GPIO_PIN_RESET)
				{
					return Status.Pressed_Key = i+30;
				}
			}

			Set_Col_LOW(0);

			Status.Pressed_Key = 0;
			Status.Rows.ROW6 = IDLE;
			Status.Scan_Rows = RESET;
		break;
	}

	return 0;
}

void HID_Buf_Routine(void)
{
	if(Status.Pressed_Key != 0)
	{
		Status.Shuttle_mode = SHTL_STOP;

		if(Status.Pressed_Key == 28)
		  Status.Knob_Mode = SHTL;
		else if(Status.Pressed_Key == 29)
		  Status.Knob_Mode = JOG;
		else if(Status.Pressed_Key == 25)
		  Status.Knob_Mode = SCRL;
		else if(Status.Pressed_Key == 1) // ESC
		{
			Status.Edit_mode = NONE_MODE;

			HID_Status.buff[0] = KeyMacro[38]; //ESC
			HID_Status.buff[1] = KeyMacro[35]; //Deselect All
			HID_Status.buff[2] = KeyMacro[39]; //Selection mode

			Status.NumOfKeys = 3;
			HID_Status.buff_ready = SET;
		}
		else if(Status.Pressed_Key == 4) // Smart Insert
		{
			HID_Status.buff[0] = KeyMacro[33];
			HID_Status.buff[1] = KeyMacro[34];
			HID_Status.buff[2] = KeyMacro[35];

			Status.NumOfKeys = 3;
			HID_Status.buff_ready = SET;
		}
		else if(Status.Pressed_Key == 11) // Standard Transition
		{
			HID_Status.buff[0] = KeyMacro[36];
			HID_Status.buff[1] = KeyMacro[37];
			HID_Status.buff[2] = KeyMacro[35];

			Status.NumOfKeys = 3;
			HID_Status.buff_ready = SET;
		}
		else if(Status.Pressed_Key == 18) // Enable/Disable clip
		{
			HID_Status.buff[0] = KeyMacro[40];
			HID_Status.buff[1] = KeyMacro[41];
			HID_Status.buff[2] = KeyMacro[35];

			Status.NumOfKeys = 3;
			HID_Status.buff_ready = SET;
		}
		else if(Status.Pressed_Key == 22) // Change speed
		{
			HID_Status.buff[0] = KeyMacro[42];
			HID_Status.buff[1] = KeyMacro[43];
			HID_Status.buff[2] = KeyMacro[35];

			Status.NumOfKeys = 3;
			HID_Status.buff_ready = SET;
		}
		else if(Status.Pressed_Key == 23) // Show curve
		{
			HID_Status.buff[0] = KeyMacro[44];
			HID_Status.buff[1] = KeyMacro[45];
			HID_Status.buff[2] = KeyMacro[35];

			Status.NumOfKeys = 3;
			HID_Status.buff_ready = SET;
		}
		else if((Status.Pressed_Key == 19) || (Status.Pressed_Key == 20) ||
				(Status.Pressed_Key == 24) || (Status.Pressed_Key == 32) ||
				(Status.Pressed_Key == 12) || (Status.Pressed_Key == 13)) // If long press key is pressed
		{
			/* Nothing to do */
		}
		else
		{
			HID_Status.buff[0] = KeyMacro[Status.Pressed_Key];

			HID_Status.buff_ready = SET;
		}
	}
}
