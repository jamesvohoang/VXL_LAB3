/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RED0_Pin GPIO_PIN_0
#define RED0_GPIO_Port GPIOA
#define RED1_Pin GPIO_PIN_1
#define RED1_GPIO_Port GPIOA
#define RED2_Pin GPIO_PIN_2
#define RED2_GPIO_Port GPIOA
#define RED3_Pin GPIO_PIN_3
#define RED3_GPIO_Port GPIOA
#define YEL0_Pin GPIO_PIN_4
#define YEL0_GPIO_Port GPIOA
#define YEL1_Pin GPIO_PIN_5
#define YEL1_GPIO_Port GPIOA
#define YEL2_Pin GPIO_PIN_6
#define YEL2_GPIO_Port GPIOA
#define YEL3_Pin GPIO_PIN_7
#define YEL3_GPIO_Port GPIOA
#define SEG0_Pin GPIO_PIN_0
#define SEG0_GPIO_Port GPIOB
#define SEG1_Pin GPIO_PIN_1
#define SEG1_GPIO_Port GPIOB
#define SEG2_Pin GPIO_PIN_2
#define SEG2_GPIO_Port GPIOB
#define BTN2_Pin GPIO_PIN_12
#define BTN2_GPIO_Port GPIOB
#define BTN1_Pin GPIO_PIN_13
#define BTN1_GPIO_Port GPIOB
#define BTN0_Pin GPIO_PIN_14
#define BTN0_GPIO_Port GPIOB
#define GRN0_Pin GPIO_PIN_8
#define GRN0_GPIO_Port GPIOA
#define GRN1_Pin GPIO_PIN_9
#define GRN1_GPIO_Port GPIOA
#define GRN2_Pin GPIO_PIN_10
#define GRN2_GPIO_Port GPIOA
#define GRN3_Pin GPIO_PIN_11
#define GRN3_GPIO_Port GPIOA
#define SEG3_Pin GPIO_PIN_3
#define SEG3_GPIO_Port GPIOB
#define SEG4_Pin GPIO_PIN_4
#define SEG4_GPIO_Port GPIOB
#define SEG5_Pin GPIO_PIN_5
#define SEG5_GPIO_Port GPIOB
#define SEG6_Pin GPIO_PIN_6
#define SEG6_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
