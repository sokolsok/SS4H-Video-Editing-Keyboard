/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Created by: Smart Solutions for Home - Sebastian Sokołowski
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "as5601.h"
#include "keys.h"
#include "knob.h"
#include "usbd_hid.h"
#include "nextion.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
void KnobModeLED(uint8_t led);
void HID_Send(RDY_Key_t *buff);
void LED_Routine(void);
void LongPress_Routine(void);

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
Status_t Status;
HID_Status_t HID_Status;

extern USBD_HandleTypeDef hUsbDeviceFS;
extern RDY_Key_t KeyMacro[], KnobMacro[];

uint8_t i;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM10_Init();
  MX_TIM2_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_USB_DEVICE_Init();
  MX_TIM7_Init();
  MX_TIM6_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start_IT(&htim6);
  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);

  /* Wait for Nextion display buffer */
  HAL_UART_Receive_IT(&huart1, (uint8_t *)Status.NextionRX_buff, 3);

  /* Set the required Encoder resolution and save it. It is enough to call this function only once. */
  //SetResolution(0x07); //1024 ticks per rotation
  //BurnSettings();

  /* Default state */
  HAL_GPIO_WritePin(LEDS_A_GPIO_Port, LEDS_A_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LEDS_B_GPIO_Port, LEDS_B_Pin, GPIO_PIN_SET);

  Status.NumOfKeys = 1;
  Status.Knob_Mode = JOG;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /* Routines are triggered every 1 ms. */
	  if(Status.Flags.FLAG_1MS)
	  {
		  Status.Flags.FLAG_1MS = RESET;

		  KnobRoutine();
		  HID_Buf_Routine();
		  LED_Routine();
		  LongPress_Routine();
	  }

	  /* Send report - USB */
	  if(HID_Status.buff_ready == SET)
	  {
		  for(i = 0; i < Status.NumOfKeys; i++)
		  {
			  USBD_HID_SendReport(&hUsbDeviceFS, &HID_Status.buff[i], sizeof(HID_Status.buff[i])); //Press the appropriate key
			  HAL_Delay(20);
			  USBD_HID_SendReport(&hUsbDeviceFS, &KeyMacro[0], sizeof(KeyMacro[0])); //After 20ms release all keys

			  /* If you are using a macro and you need more than one key (one after the other) */
			  if(Status.NumOfKeys > 1)
				  HAL_Delay(100);
		  }

		  Status.NumOfKeys = 1;
		  HID_Status.buff_ready = RESET;
	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* After pressing a key and turning the knob */
void LongPress_Routine(void)
{
	if(Status.Pressed_Key == 19)
		Status.Edit_mode = ZOOM;
	else if(Status.Pressed_Key == 12) //SLIP
	{
		Status.Edit_mode = SLIP;

		if(Status.LP_Key_state.KEY_SLIP == KEY_IDLE)
		{
			Status.LP_Key_state.KEY_SLIP = KEY_JUST_PRESSED;

			HID_Status.buff[0] = KeyMacro[Status.Pressed_Key];
			HID_Status.buff_ready = SET;
		}
		else if(Status.LP_Key_state.KEY_SLIP == KEY_JUST_PRESSED)
			Status.LP_Key_state.KEY_SLIP = KEY_PRESSED;
	}
	else if(Status.Pressed_Key == 13) //SLIDE
	{
		Status.Edit_mode = SLIDE;

		if(Status.LP_Key_state.KEY_SLIDE == KEY_IDLE)
		{
			Status.LP_Key_state.KEY_SLIDE = KEY_JUST_PRESSED;

			HID_Status.buff[0] = KeyMacro[Status.Pressed_Key];
			HID_Status.buff_ready = SET;
		}
		else if(Status.LP_Key_state.KEY_SLIDE == KEY_JUST_PRESSED)
			Status.LP_Key_state.KEY_SLIDE = KEY_PRESSED;
	}
	else if(Status.Pressed_Key == 32) //Audio level
	{
		Status.Edit_mode = AUDIO;

		if(Status.LP_Key_state.KEY_AUDIO == KEY_IDLE)
		{
			Status.LP_Key_state.KEY_AUDIO = KEY_JUST_PRESSED;

			HID_Status.buff[0] = KeyMacro[40]; //Select clip
			HID_Status.buff_ready = SET;
		}
		else if(Status.LP_Key_state.KEY_AUDIO == KEY_JUST_PRESSED)
			Status.LP_Key_state.KEY_AUDIO = KEY_PRESSED;
	}
	else if(Status.Pressed_Key == 24)
	{
		Status.Edit_mode = SWAP;

		if(Status.LP_Key_state.KEY_SWAP == KEY_IDLE)
		{
			Status.LP_Key_state.KEY_SWAP = KEY_JUST_PRESSED;

			HID_Status.buff[0] = KeyMacro[40]; //Select clip
			HID_Status.buff_ready = SET;
		}
		else if(Status.LP_Key_state.KEY_SWAP == KEY_JUST_PRESSED)
			Status.LP_Key_state.KEY_SWAP = KEY_PRESSED;
	}
	else if(Status.Pressed_Key == 20)
		Status.Edit_mode = SNAP;
	else
	{
		Status.Edit_mode = NONE_MODE;

		/* SWAP */
		if(Status.LP_Key_state.KEY_SWAP == KEY_PRESSED)
		{
			Status.LP_Key_state.KEY_SWAP = KEY_JUST_RELEASED;

			HID_Status.buff[0] = KeyMacro[35]; //Deselect clip
			HID_Status.buff_ready = SET;
		}
		else if(Status.LP_Key_state.KEY_SWAP == KEY_JUST_RELEASED)
			Status.LP_Key_state.KEY_SWAP = KEY_IDLE;

		/* AUDIO */
		if(Status.LP_Key_state.KEY_AUDIO == KEY_PRESSED)
		{
			Status.LP_Key_state.KEY_AUDIO = KEY_JUST_RELEASED;

			HID_Status.buff[0] = KeyMacro[35]; //Deselect clip
			HID_Status.buff_ready = SET;
		}
		else if(Status.LP_Key_state.KEY_AUDIO == KEY_JUST_RELEASED)
			Status.LP_Key_state.KEY_AUDIO = KEY_IDLE;

		/* SLIP */
		if(Status.LP_Key_state.KEY_SLIP == KEY_PRESSED)
		{
			Status.LP_Key_state.KEY_SLIP = KEY_JUST_RELEASED;

			HID_Status.buff[0] = KeyMacro[35]; //Deselect All
			HID_Status.buff[1] = KeyMacro[39]; //Selection mode

			Status.NumOfKeys = 2;
			HID_Status.buff_ready = SET;
		}
		else if(Status.LP_Key_state.KEY_SLIP == KEY_JUST_RELEASED)
			Status.LP_Key_state.KEY_SLIP = KEY_IDLE;

		/* SLIDE */
		if(Status.LP_Key_state.KEY_SLIDE == KEY_PRESSED)
		{
			Status.LP_Key_state.KEY_SLIDE = KEY_JUST_RELEASED;

			HID_Status.buff[0] = KeyMacro[35]; //Deselect All
			HID_Status.buff[1] = KeyMacro[39]; //Selection mode

			Status.NumOfKeys = 2;
			HID_Status.buff_ready = SET;
		}
		else if(Status.LP_Key_state.KEY_SLIDE == KEY_JUST_RELEASED)
			Status.LP_Key_state.KEY_SLIDE = KEY_IDLE;
	}

}

/* Knob mode */
void LED_Routine(void)
{
	if(Status.Knob_Mode == SHTL)
	  KnobModeLED(1);
	else if(Status.Knob_Mode == JOG)
	  KnobModeLED(2);
	else if(Status.Knob_Mode == SCRL)
	  KnobModeLED(3);
}

/* Knob ring of LEDs */
void KnobModeLED(uint8_t led)
{
	switch(led)
	{
		case 1:
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
		break;
		case 2:
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
		break;
		case 3:
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
		break;
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
