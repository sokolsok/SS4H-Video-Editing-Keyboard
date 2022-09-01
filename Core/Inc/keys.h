/*
 * keys.h
 *
 * Created by: Smart Solutions for Home - Sebastian Sokołowski
 *
 */

#ifndef INC_KEYS_H_
#define INC_KEYS_H_

#include "main.h"
#include "tim.h"
#include "usbd_hid.h"
#include "usart.h"

#define DEBOUNCING_TIME		20 //ms

typedef enum{
    /* Zero, does not correspond to any key. */
    KEY_None = 0,

    /* Keycode definitions. */
    KEY_A = 4,
    KEY_B = 5,
    KEY_C = 6,
    KEY_D = 7,
    KEY_E = 8,
    KEY_F = 9,
    KEY_G = 10,
    KEY_H = 11,
    KEY_I = 12,
    KEY_J = 13,
    KEY_K = 14,
    KEY_L = 15,
    KEY_M = 16,
    KEY_N = 17,
    KEY_O = 18,
    KEY_P = 19,
    KEY_Q = 20,
    KEY_R = 21,
    KEY_S = 22,
    KEY_T = 23,
    KEY_U = 24,
    KEY_V = 25,
    KEY_W = 26,
    KEY_X = 27,
    KEY_Y = 28,
    KEY_Z = 29,
    KEY_1 = 30,
    KEY_2 = 31,
    KEY_3 = 32,
    KEY_4 = 33,
    KEY_5 = 34,
    KEY_6 = 35,
    KEY_7 = 36,
    KEY_8 = 37,
    KEY_9 = 38,
    KEY_0 = 39,
    KEY_Escape = 41,
    KEY_Delete = 42,
    KEY_Tab = 43,
    KEY_Space = 44,
    KEY_Minus = 45,
    KEY_Equals = 46,
    KEY_LeftBracket = 47,
    KEY_RightBracket = 48,
    KEY_Backslash = 49,
    KEY_Semicolon = 51,
    KEY_Quote = 52,
    KEY_Grave = 53,
    KEY_Comma = 54,
    KEY_Period = 55,
    KEY_Slash = 56,
    KEY_CapsLock = 57,
    KEY_F1 = 58,
    KEY_F2 = 59,
    KEY_F3 = 60,
    KEY_F4 = 61,
    KEY_F5 = 62,
    KEY_F6 = 63,
    KEY_F7 = 64,
    KEY_F8 = 65,
    KEY_F9 = 66,
    KEY_F10 = 67,
    KEY_F11 = 68,
    KEY_F12 = 69,
    KEY_PrintScreen = 70,
    KEY_ScrollLock = 71,
    KEY_Pause = 72,
    KEY_Insert = 73,
    KEY_Home = 74,
    KEY_PageUp = 75,
    KEY_DeleteForward = 76,
    KEY_End = 77,
    KEY_PageDown = 78,
    KEY_Right = 79,
    KEY_Left = 80,
    KEY_Down = 81,
    KEY_Up = 82,
    KP_NumLock = 83,
    KP_Divide = 84,
    KP_Multiply = 85,
    KP_Subtract = 86,
    KP_Add = 87,
    KP_Enter = 88,
    KP_1 = 89,
    KP_2 = 90,
    KP_3 = 91,
    KP_4 = 92,
    KP_5 = 93,
    KP_6 = 94,
    KP_7 = 95,
    KP_8 = 96,
    KP_9 = 97,
    KP_0 = 98,
    KP_Point = 99,
    KEY_NonUSBackslash = 100,
    KP_Equals = 103,
    KEY_F13 = 104,
    KEY_F14 = 105,
    KEY_F15 = 106,
    KEY_F16 = 107,
    KEY_F17 = 108,
    KEY_F18 = 109,
    KEY_F19 = 110,
    KEY_F20 = 111,
    KEY_F21 = 112,
    KEY_F22 = 113,
    KEY_F23 = 114,
    KEY_F24 = 115,
    KEY_Help = 117,
    KEY_Menu = 118,
    KEY_Mute = 127,
    KEY_SysReq = 154,
    KEY_Return = 158,
    KP_Clear = 216,
    KP_Decimal = 220,
    KEY_LeftControl = 224,
    KEY_LeftShift = 225,
    KEY_LeftAlt = 226,
    KEY_LeftGUI = 227,
    KEY_RightControl = 228,
    KEY_RightShift = 229,
    KEY_RightAlt = 230,
    KEY_RightGUI = 231
}Key_t;

typedef enum{
	MOD_None = 0x00,
	MOD_CTRL_L = 0x01,
	MOD_SHIFT_L = 0x02,
	MOD_ALT_L = 0x04,
	MOD_GUI_L = 0x08,
	MOD_CTRL_R = 0x10,
	MOD_SHIFT_R = 0x20,
	MOD_ALT_R = 0x40,
	MOD_GUI_R = 0x80
}Modifier_t;



typedef struct{
	Modifier_t	MODIFIER;
	uint8_t 	RESERVED;
	Key_t 		KEYCODE1;
	uint8_t 	KEYCODE2;
	uint8_t 	KEYCODE3;
	uint8_t 	KEYCODE4;
	uint8_t 	KEYCODE5;
	uint8_t 	KEYCODE6;
}RDY_Key_t;

/* HID Status */
typedef struct{
	FlagStatus			buff_ready;
	RDY_Key_t			buff[3];
}HID_Status_t;

uint8_t Scan_Routine(uint8_t no);
void SendReportHID(void);
void SendReportHID_clean(void);
void HID_Buf_Routine(void);

#endif /* INC_KEYS_H_ */
