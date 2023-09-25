/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
void clearAllclock(){
	for(int i=0;i<12;i++){
		HAL_GPIO_WritePin(GPIOA, LED_12_Pin <<(i), SET);
	}
}

void setNumberOnClock(int num){
	HAL_GPIO_WritePin(GPIOA, LED_12_Pin<<(num), RESET);
}
void clearNumberOnClock(int num){
	HAL_GPIO_WritePin(GPIOA, LED_12_Pin <<(num), SET);
}

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

//    int counter=0;	//For Ex6+7+8+9
  /*Ex10*/
  int second = 0;
  int minute = 11;
  int hour = 10;
  int change_hour = 0;
  int change_minute = 0;
  setNumberOnClock(second);
  setNumberOnClock(minute);
  setNumberOnClock(hour);
  while (1)
  {
    /* USER CODE END WHILE */
	  // All pins were set to high at the beginning

	  /*Ex6+7+8+9*/
//	  int temp = counter %12;
////	  HAL_GPIO_WritePin(GPIOA, LED_12_Pin <<(temp), RESET);
//	  setNumberOnClock(temp);
//	  counter++;
//	  if(counter >12) {
//		  clearNumberOnClock(6);	// For Ex9 clear number on a specific pin
//		  clearAllclock();
//		  counter = 0;
//	  }
//	  HAL_Delay(1000);
	  /*Ex10*/
	  // Second
	  setNumberOnClock(second);
	  if(second == 0 )	clearNumberOnClock(11);
	  else if(second != 0)	clearNumberOnClock(second - 1);

	  // Minute
	  setNumberOnClock(minute);
	  if(minute ==0 && change_minute !=0) {
		  clearNumberOnClock(11);
		  change_minute =0;
	  }else if(minute !=0 && change_minute ==1) {
		  clearNumberOnClock(minute-1);
		  change_minute =0;
	  }

	  // Hour
	  setNumberOnClock(hour);
	  if(hour ==0 && change_hour !=0) {
		  clearNumberOnClock(11);
		  change_hour =0;
	  }else if(hour !=0 && change_hour ==1) {
		  clearNumberOnClock(hour-1);
		  change_hour =0;
	  }

	  if(second == 11){
		  second = 0;
		  minute++;
		  if(minute == 12){
			  minute = 0;
			  hour++;
			  if(hour==12){
				  hour = 0;
			  }
			  change_hour = 1;
		  }
		  change_minute = 1;
		  HAL_Delay(1000);
		  continue;
	  }

	  second++;
	  HAL_Delay(1000);


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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_12_Pin|LED_12A5_Pin|LED_12A6_Pin|LED_12A7_Pin
                          |LED_12A8_Pin|LED_12A9_Pin|LED_12A10_Pin|LED_12A11_Pin
                          |LED_12A12_Pin|LED_12A13_Pin|LED_12A14_Pin|LED_12A15_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : LED_12_Pin LED_12A5_Pin LED_12A6_Pin LED_12A7_Pin
                           LED_12A8_Pin LED_12A9_Pin LED_12A10_Pin LED_12A11_Pin
                           LED_12A12_Pin LED_12A13_Pin LED_12A14_Pin LED_12A15_Pin */
  GPIO_InitStruct.Pin = LED_12_Pin|LED_12A5_Pin|LED_12A6_Pin|LED_12A7_Pin
                          |LED_12A8_Pin|LED_12A9_Pin|LED_12A10_Pin|LED_12A11_Pin
                          |LED_12A12_Pin|LED_12A13_Pin|LED_12A14_Pin|LED_12A15_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
