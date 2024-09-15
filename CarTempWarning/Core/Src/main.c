/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
#include "bmp280.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "keyscan.h"

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

//存储设置的温度
int32_t TsetYes = 28;
int32_t TsetNo = 30;
//存储检测的温度
float T = 0;
//用于存储转换成字符串的设置温度
char tempToSetYes[5];
char tempToSetNo[5];
//用于存储转换成字符串的检测温度
char tempToShow[6];

int t = 0;

int setFlag = 0;
int peopleFlag = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void oledShowAll(void);
void tempWarning(void);
void KeyTask(int);
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
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
	

	OLED_Init();
	OLED_DisPlay_On();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
	OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	OLED_Clear();
	OLED_Refresh();
	HAL_UART_Transmit(&huart1,(const uint8_t *)"OLED_InitOK",strlen("OLED_InitOK"),100);
	HAL_UART_Transmit(&huart1,(const uint8_t *)"\r\n",strlen("\r\n"),100);
	
	BMP280_InitALL();
	HAL_UART_Transmit(&huart1,(const uint8_t *)"BMP_InitOK",strlen("BMP_InitOK"),100);
	HAL_UART_Transmit(&huart1,(const uint8_t *)"\r\n",strlen("\r\n"),100);
	HAL_UART_Transmit(&huart1,(const uint8_t *)"SysStart\r\n",strlen("SysStart\r\n"),100);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		KeyTask(keyScan());
		
		//运行模式
		if(setFlag == 0)
		{
			//光电传感器检测是否有人
			if(HAL_GPIO_ReadPin(PeopleDetect_GPIO_Port,PeopleDetect_Pin) == 0)
			{
					peopleFlag = 1;
			}
			else{peopleFlag = 0;}
		
			oledShowAll();
			
			
			t++;
			if(t >=5)
			{
				tempWarning();
				t = 0;
			}
		}
		
		//设置模式
		else if(setFlag == 1)
		{
			oledShowAll();
			
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void oledShowAll()
{
	//温度检测
		T = BMP280_GetTemperature()/100.0;
	//转换成字符串
		snprintf(tempToShow,sizeof(tempToShow),"%.2f",T);
		snprintf(tempToSetYes,sizeof(tempToSetYes),"%d",TsetYes);
		snprintf(tempToSetNo,sizeof(tempToSetNo),"%d",TsetNo);
	//OLED显示
		OLED_ShowString(0,0,(uint8_t *)"Mode:",16,1);
		if(setFlag == 0)
			OLED_ShowString(40,0,(uint8_t *)"Running",16,1);
		else
			OLED_ShowString(40,0,(uint8_t *)"Setting",16,1);
		
		
		OLED_ShowString(0,16,(uint8_t *)"People:",16,1);
		if(peopleFlag == 0)
			OLED_ShowString(56,16,(uint8_t *)"No ",16,1);
		else
			OLED_ShowString(56,16,(uint8_t *)"Yes",16,1);
		
		OLED_ShowString(0,32,(uint8_t *)"TempNow:",16,1);
		OLED_ShowString(64,32,(uint8_t*)tempToShow,16,1);
		OLED_ShowString(0,48,(uint8_t *)"TempSet:",16,1); 
		if(peopleFlag == 0)
			OLED_ShowString(64,48,(uint8_t *)tempToSetNo,16,1);
		else
			OLED_ShowString(64,48,(uint8_t *)tempToSetYes,16,1);
	//刷新屏幕
		OLED_Refresh();
	
}



void tempWarning()
{
	//有人温度检测以及报警
		if(peopleFlag == 1)
		{
			if(T >= TsetYes)
			{
				snprintf(tempToShow,sizeof(tempToShow),"%.2f",T);
				snprintf(tempToSetYes,sizeof(tempToSetYes),"%d",TsetYes);
				HAL_GPIO_WritePin(Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_RESET);
				//发送串口消息
				HAL_UART_Transmit(&huart1, (const uint8_t *)"PersonInCar,TempWarning!!!Current:", strlen("PersonInCar,TempWarning!!!Current:"), 300);
				HAL_UART_Transmit(&huart1, (const uint8_t *)tempToShow, strlen(tempToShow), 300);
				HAL_UART_Transmit(&huart1, (const uint8_t *)"\r\nSetting:", strlen("\r\nSetting:"), 300);
				HAL_UART_Transmit(&huart1, (const uint8_t *)tempToSetYes, strlen(tempToSetYes), 300);
				HAL_UART_Transmit(&huart1, (const uint8_t *)"\r\n\r\n", strlen("\r\n\r\n"), 300);
			}
			else
			{
				HAL_GPIO_WritePin(Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_SET);
			}
		}
		
	//无人温度检测以及报警
		if(peopleFlag == 0)
		{
			if(T >= TsetNo)
			{
				snprintf(tempToShow,sizeof(tempToShow),"%.2f",T);
				snprintf(tempToSetNo,sizeof(tempToSetNo),"%d",TsetNo);
				HAL_GPIO_WritePin(Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_RESET);
				//发送串口消息
				HAL_UART_Transmit(&huart1, (const uint8_t *)"CarEmpty,TempWarning!!!Current:", strlen("CarEmpty,TempWarning!!!Current:"), 300);
				HAL_UART_Transmit(&huart1, (const uint8_t *)tempToShow, strlen(tempToShow), 300);
				HAL_UART_Transmit(&huart1, (const uint8_t *)"\r\nSetting:", strlen("\r\nSetting:"), 300);
				HAL_UART_Transmit(&huart1, (const uint8_t *)tempToSetNo, strlen(tempToSetNo), 300);
				HAL_UART_Transmit(&huart1, (const uint8_t *)"\r\n\r\n", strlen("\r\n\r\n"), 300);
			}
			else
			{
				HAL_GPIO_WritePin(Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_SET);
			}
		}
}

void KeyTask(int keynum)
{
	if(keynum == 1)
	{
		if(setFlag == 0)setFlag = 1;//进入设置
		else if(setFlag == 1)setFlag = 0;//退出设置
	}
	
	if(keynum == 2)
	{
		if(setFlag == 1)//判断是否已经进入设置
		{
			if(peopleFlag == 0)peopleFlag = 1;//进入有人温度设置
			else if(peopleFlag == 1)peopleFlag = 0;//进入无人温度设置
		}
	}
	
	if(keynum == 3)
	{
		if(setFlag == 1)//判断是否已经进入设置
		{
			if(peopleFlag == 0)TsetNo++;//无人温度设置
			else if(peopleFlag == 1)TsetYes++;//有人温度设置
		}
	}
	if(keynum == 4)
	{
		if(setFlag == 1)//判断是否已经进入设置
		{
			if(peopleFlag == 0)TsetNo--;//无人温度设置
			else if(peopleFlag == 1)TsetYes--;//有人温度设置
		}
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
