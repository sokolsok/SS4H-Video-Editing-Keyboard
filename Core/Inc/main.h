/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Created by: Smart Solutions for Home - Sebastian Sokołowski
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* Flags */
typedef struct{
	FlagStatus 		FLAG_1MS;
	FlagStatus		FLAG_50MS;
}Flag_t;

/* Knob modes */
typedef enum{
	SHTL = 0,
	JOG,
	SCRL
}Knob_Mode_t;

/* Editing modes */
typedef enum{
	NONE_MODE = 0,
	SLIP,
	SLIDE,
	AUDIO,
	ZOOM,
	SNAP,
	SWAP
}Edit_Mode_t;

/* Row State */
typedef enum{
	IDLE = 0,
	DEBOUNCED,
	PRESSED,
	RELEASED
}Row_State_t;

/* Key State */
typedef enum{
	KEY_IDLE = 0,
	KEY_JUST_PRESSED,
	KEY_PRESSED,
	KEY_JUST_RELEASED
}Key_State_t;

typedef struct{
	Key_State_t		KEY_ZOOM;
	Key_State_t		KEY_SNAP;
	Key_State_t		KEY_SWAP;
	Key_State_t		KEY_AUDIO;
	Key_State_t		KEY_SLIDE;
	Key_State_t		KEY_SLIP;
}Long_Press_Key_t;

typedef struct{
	Row_State_t		ROW1;
	Row_State_t		ROW2;
	Row_State_t		ROW3;
	Row_State_t		ROW4;
	Row_State_t		ROW5;
	Row_State_t		ROW6;
}Rows_t;

/* Shuttle mode */
typedef enum{
	SHTL_STOP = 0,
	FORW_1,
	FORW_2,
	FORW_4,
	FORW_8,
	FORW_16,
	FORW_32,
	FORW_64,
	REW_1,
	REW_2,
	REW_4,
	REW_8,
	REW_16,
	REW_32,
	REW_64
}Shuttle_mode_t;

typedef struct{
	Rows_t				Rows;
	uint8_t				Scan_Rows;
	uint8_t				Pressed_Key;
	uint8_t				NumOfKeys;
	Edit_Mode_t			Edit_mode;
	int16_t				KnobCounetr;
	int16_t				KnobCounetr_old;
	uint8_t				KnobDir;
	uint8_t				KonbRotated;
	Knob_Mode_t			Knob_Mode;
	uint16_t			Knob_Speed;
	uint32_t			Knob_Speed_counter;
	Flag_t				Flags;
	Shuttle_mode_t		Shuttle_mode;
	Long_Press_Key_t	LP_Key_state;
	uint8_t				NextionRX_buff[7];
}Status_t;

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LEDS_B_Pin GPIO_PIN_13
#define LEDS_B_GPIO_Port GPIOC
#define LEDS_A_Pin GPIO_PIN_14
#define LEDS_A_GPIO_Port GPIOC
#define ROW4_Pin GPIO_PIN_0
#define ROW4_GPIO_Port GPIOA
#define ROW4_EXTI_IRQn EXTI0_IRQn
#define ROW3_Pin GPIO_PIN_1
#define ROW3_GPIO_Port GPIOA
#define ROW3_EXTI_IRQn EXTI1_IRQn
#define ROW2_Pin GPIO_PIN_2
#define ROW2_GPIO_Port GPIOA
#define ROW2_EXTI_IRQn EXTI2_IRQn
#define ROW1_Pin GPIO_PIN_3
#define ROW1_GPIO_Port GPIOA
#define ROW1_EXTI_IRQn EXTI3_IRQn
#define LED3_Pin GPIO_PIN_5
#define LED3_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_6
#define LED2_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_7
#define LED1_GPIO_Port GPIOA
#define COL6_Pin GPIO_PIN_2
#define COL6_GPIO_Port GPIOB
#define EEPROM_SCL_Pin GPIO_PIN_10
#define EEPROM_SCL_GPIO_Port GPIOB
#define EEPROM_SDA_Pin GPIO_PIN_11
#define EEPROM_SDA_GPIO_Port GPIOB
#define COL2_Pin GPIO_PIN_12
#define COL2_GPIO_Port GPIOB
#define COL3_Pin GPIO_PIN_13
#define COL3_GPIO_Port GPIOB
#define COL1_Pin GPIO_PIN_14
#define COL1_GPIO_Port GPIOB
#define COL5_Pin GPIO_PIN_15
#define COL5_GPIO_Port GPIOB
#define COL4_Pin GPIO_PIN_8
#define COL4_GPIO_Port GPIOA
#define ENC_PUSH_Pin GPIO_PIN_10
#define ENC_PUSH_GPIO_Port GPIOA
#define ENC_A_Pin GPIO_PIN_15
#define ENC_A_GPIO_Port GPIOA
#define ENC_B_Pin GPIO_PIN_3
#define ENC_B_GPIO_Port GPIOB
#define ROW5_Pin GPIO_PIN_4
#define ROW5_GPIO_Port GPIOB
#define ROW5_EXTI_IRQn EXTI4_IRQn
#define ROW6_Pin GPIO_PIN_5
#define ROW6_GPIO_Port GPIOB
#define ROW6_EXTI_IRQn EXTI9_5_IRQn
#define NEXTION_TX_Pin GPIO_PIN_6
#define NEXTION_TX_GPIO_Port GPIOB
#define NEXTION_RX_Pin GPIO_PIN_7
#define NEXTION_RX_GPIO_Port GPIOB
#define ENC_SCL_Pin GPIO_PIN_8
#define ENC_SCL_GPIO_Port GPIOB
#define ENC_SDA_Pin GPIO_PIN_9
#define ENC_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
