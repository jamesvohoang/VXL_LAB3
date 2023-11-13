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
typedef enum
{
  RED1_GREEN2,
  RED1_YELLOW2,
  GREEN1_RED2,
  YELLOW1_RED2
}TrafficLightColor;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

uint8_t segLedIndex = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

void Scan7SEG(uint8_t val0, uint8_t val1)
{
  if(timer2_flag)
  {
    // Scan 7seg Leds
    Disable7SEG(segLedIndex);
    segLedIndex++;
    if(segLedIndex >= 4)
    {
      segLedIndex = 0;
    }
    
    switch (segLedIndex)
    {
      case 0:
        display7SEG(val0/10);
        break;
      case 1:
        display7SEG(val0%10);
        break;
      case 2:
        display7SEG(val1/10);
        break;
      case 3:
        display7SEG(val1%10);
        break;
      
      default:
        break;
    }
    Enable7SEG(segLedIndex);

    // set timer 2 in 2Hz
    setTimer2(50);
  }
}

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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  uint8_t count0 = 0;
  uint8_t count1 = 0;
  TrafficLightColor trafficLightState = 4;

  // Initialize traffic system
  HAL_TIM_Base_Start_IT(&htim2);
  modeState = NORMAL;
  TurnAllLightsOff();
  DisableAllSegs();

  // set timer 1 in 1Hz
  setTimer1(100);
  // set timer 2 in 2Hz. Use for scan 7Segment Leds
  setTimer2(50);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    fsm_for_input_processing();

    if(modeState != NORMAL)
    {
      if(timer1_flag)
      {
        switch (modeState)
        {
        case MODIFY_FOR_RED:
          ToggleAllRedLeds();
          Scan7SEG(modeState, durationOfRed);
          break;

        case MODIFY_FOR_YELLOW:
          ToggleAllYellowLeds();
          Scan7SEG(modeState, durationOfYellow);
          break;

        case MODIFY_FOR_GREEN:
          ToggleAllGreenLeds();
          Scan7SEG(modeState, durationOfGreen);
          break;
        
        default:
          break;
        }
        // set timer 1 in 2Hz
        setTimer1(50);
      }
    }
    else
    {
      if(timer1_flag)
      {
        // Check does need to Change Traffic state
        if(!count0 || !count1)
        {
          if(trafficLightState >= 4)
            trafficLightState = 0;
          else
            trafficLightState++;
          
          switch (trafficLightState)
          {
          case RED1_GREEN2:
            // Turn lights on
            TurnAllLightsOff();
            HAL_GPIO_WritePin(RED0_GPIO_Port, RED0_Pin, 0);
            HAL_GPIO_WritePin(GRN1_GPIO_Port, GRN1_Pin, 0);

            // Set counting down
            count0 = durationOfRed + 1;
            count1 = durationOfGreen + 1;
            break;

          case RED1_YELLOW2:
            // Turn lights on
            TurnAllLightsOff();
            HAL_GPIO_WritePin(RED0_GPIO_Port, RED0_Pin, 0);
            HAL_GPIO_WritePin(YEL1_GPIO_Port, YEL1_Pin, 0);

            // Set counting down
            //count0 = durationOfRed + 1;
            count1 = durationOfYellow;
            break;

          case GREEN1_RED2:
            // Turn lights on
            TurnAllLightsOff();
            HAL_GPIO_WritePin(GRN0_GPIO_Port, GRN0_Pin, 0);
            HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 0);

            // Set counting down
            count0 = durationOfGreen + 1;
            count1 = durationOfRed + 1;
            break;

          case YELLOW1_RED2:
            TurnAllLightsOff();
            HAL_GPIO_WritePin(YEL0_GPIO_Port, YEL0_Pin, 0);
            HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 0);

            // Set counting down
            count0 = durationOfYellow;
            //count1 = durationOfRed + 1;
            break;

          default:
            break;
          }
        }
        count0--;
        count1--;
        
        setTimer1(100);
      }

      Scan7SEG(count0, count1);
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    //HAL_Delay(10);
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RED0_Pin|RED1_Pin|RED2_Pin|RED3_Pin
                          |YEL0_Pin|YEL1_Pin|YEL2_Pin|YEL3_Pin
                          |GRN0_Pin|GRN1_Pin|GRN2_Pin|GRN3_Pin
                          |EN3_Pin|EN0_Pin|EN1_Pin|EN2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
                          |SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RED0_Pin RED1_Pin RED2_Pin RED3_Pin
                           YEL0_Pin YEL1_Pin YEL2_Pin YEL3_Pin
                           GRN0_Pin GRN1_Pin GRN2_Pin GRN3_Pin
                           EN3_Pin EN0_Pin EN1_Pin EN2_Pin */
  GPIO_InitStruct.Pin = RED0_Pin|RED1_Pin|RED2_Pin|RED3_Pin
                          |YEL0_Pin|YEL1_Pin|YEL2_Pin|YEL3_Pin
                          |GRN0_Pin|GRN1_Pin|GRN2_Pin|GRN3_Pin
                          |EN3_Pin|EN0_Pin|EN1_Pin|EN2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG0_Pin SEG1_Pin SEG2_Pin SEG3_Pin
                           SEG4_Pin SEG5_Pin SEG6_Pin */
  GPIO_InitStruct.Pin = SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
                          |SEG4_Pin|SEG5_Pin|SEG6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN2_Pin BTN1_Pin BTN0_Pin */
  GPIO_InitStruct.Pin = BTN2_Pin|BTN1_Pin|BTN0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim -> Instance == TIM2)
  {
    timerRun();
    button_reading();
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
