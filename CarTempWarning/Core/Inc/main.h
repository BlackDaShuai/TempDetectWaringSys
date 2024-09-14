/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#define KeyUSER_Pin GPIO_PIN_0
#define KeyUSER_GPIO_Port GPIOA
#define Key1_Pin GPIO_PIN_1
#define Key1_GPIO_Port GPIOA
#define Key2_Pin GPIO_PIN_2
#define Key2_GPIO_Port GPIOA
#define Key3_Pin GPIO_PIN_3
#define Key3_GPIO_Port GPIOA
#define Key4_Pin GPIO_PIN_4
#define Key4_GPIO_Port GPIOA
#define OLEDRES_Pin GPIO_PIN_6
#define OLEDRES_GPIO_Port GPIOA
#define OLEDDC_Pin GPIO_PIN_0
#define OLEDDC_GPIO_Port GPIOB
#define PeopleDetect_Pin GPIO_PIN_1
#define PeopleDetect_GPIO_Port GPIOB
#define LEDB_Pin GPIO_PIN_2
#define LEDB_GPIO_Port GPIOB
#define Buzzer_Pin GPIO_PIN_10
#define Buzzer_GPIO_Port GPIOB
#define Key5_Pin GPIO_PIN_12
#define Key5_GPIO_Port GPIOB
#define Key6_Pin GPIO_PIN_13
#define Key6_GPIO_Port GPIOB
#define Key7_Pin GPIO_PIN_14
#define Key7_GPIO_Port GPIOB
#define Key8_Pin GPIO_PIN_15
#define Key8_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
