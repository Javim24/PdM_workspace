/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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

typedef struct {
	uint16_t pin;
	GPIO_TypeDef* port;
} led_typedef; 				//estructura para guardar el pin y el puerto de cada led

/*
 * los pines de led están definidos en CubeMx:
 * ledB --> PIN A1
 * ledG --> PIN A2
 * ledR --> PIN A3
 */

led_typedef ledRed = {ledR_Pin, ledR_GPIO_Port};
led_typedef ledGreen = {ledG_Pin, ledG_GPIO_Port};
led_typedef ledBlue = {ledB_Pin, ledB_GPIO_Port};

led_typedef *secuencia1[] = {&ledRed, &ledGreen, &ledBlue}; //secuencia 1: LED1, LED2, LED3
led_typedef *secuencia2[] = {&ledRed, &ledBlue, &ledGreen}; //secuencia 2: LED1, LED3, LED2



const uint8_t NUM_LEDS = 3;
const uint16_t ON_TIME_MS = 200;

led_typedef **secuencia_actual;	//almacena qué secuencia se está utilizando actualmente, se modifica cuando se presiona el botón
uint8_t btnPressed; //el botón se encuentra conectado al pin B1, con una resistencia de pull-up. cuando lo presiono el pin lee el valor 0
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

//funciones que uso para encender o apagar uno o todos los leds
void led_on(led_typedef*);
void led_off(led_typedef*);
void led_off_all(led_typedef*[]);

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  secuencia_actual = secuencia1;
  led_off_all(secuencia_actual);
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  for(int i=0; i<NUM_LEDS; i++){
		  led_on(secuencia_actual[i]);
		  HAL_Delay(ON_TIME_MS);
		  led_off_all(secuencia_actual);
		  HAL_Delay(ON_TIME_MS);
	  }


	  btnPressed = !HAL_GPIO_ReadPin(btn_GPIO_Port, btn_Pin);

	  if(btnPressed){
		  if(secuencia_actual == secuencia1){
			  secuencia_actual = secuencia2;
		  }
		  else{
			  secuencia_actual = secuencia1;
		  }
	  }
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
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ledB_Pin|ledG_Pin|ledR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ledB_Pin ledG_Pin ledR_Pin */
  GPIO_InitStruct.Pin = ledB_Pin|ledG_Pin|ledR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : btn_Pin */
  GPIO_InitStruct.Pin = btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(btn_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* los leds están conectados a los pines de la placa en la configuración open-drain.
 * Por lo tanto para encender un led, el estado del pin debe ser 0 (GPIO_PIN_RESET),
 * y para apagarlo el estado debe ser 1 (GPIO_PIN_SET).
 * */

void led_on(led_typedef *led){
	HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);
}

void led_off(led_typedef *led){
	HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_SET);
}

void led_off_all(led_typedef *leds[]){
	for(int i=0; i<NUM_LEDS; i++){
		led_off(leds[i]);
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
