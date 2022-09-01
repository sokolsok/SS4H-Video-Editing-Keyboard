/*
 * nextion.c
 *
 * Created by: Smart Solutions for Home - Sebastian Sokołowski
 *
 */


#include "nextion.h"

extern Status_t Status;
extern HID_Status_t HID_Status;

RDY_Key_t NextionMacro[14] =
{
		{MOD_None, 0,KEY_None},								//0 - NA
		{MOD_None, 0, KEY_None},							//1 - NA
		{MOD_SHIFT_L, 0, KEY_2},							//2 - Media Page
		{MOD_SHIFT_L, 0, KEY_3},							//3 - Cut Page
		{MOD_SHIFT_L, 0, KEY_4},							//4 - Edit Page
		{MOD_SHIFT_L, 0, KEY_6},							//5 - Color Page
		{MOD_CTRL_L, 0, KEY_Z},								//6 - Undo
		{MOD_CTRL_L | MOD_SHIFT_L, 0, KEY_Z},				//7 - Redo
		{MOD_SHIFT_L, 0, KEY_9},							//8 - Project Settings
		{MOD_CTRL_L, 0, KEY_S},								//9 - Save
		{MOD_CTRL_L, 0, KEY_V},								//10 - Copy
		{MOD_ALT_L, 0, KEY_V},								//11 - Cut
		{MOD_CTRL_L, 0, KEY_C},								//12 - Paste
		{MOD_CTRL_L, 0, KEY_X}								//13 - Paste Attributes
};

/* Callback after receiving a message from the display */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	HID_Status.buff[0] = NextionMacro[Status.NextionRX_buff[2]];

	HID_Status.buff_ready = SET;

	HAL_UART_Receive_IT(&huart1, (uint8_t *)Status.NextionRX_buff, 7);
}
