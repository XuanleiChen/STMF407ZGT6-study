/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdbool.h>

#include "6Bit_SegDisplay.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
void Seg_Control(uint16_t Wei,uint16_t Duan);
void Seg_Display(uint16_t a,uint16_t b,uint16_t c,uint16_t d,uint16_t e,uint16_t f);
void Time_Control(uint64_t Time_Value);
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t count=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


bool Key_Read(void)
{
	//uint16_t start_time=0;
	bool Key_Val=false;
	
	if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_8)==GPIO_PIN_SET){
		HAL_Delay(15);
		while(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_8)==GPIO_PIN_SET){
			Seg_Display(count/100000%10,count/10000%10,count/1000%10,count/100%10,count/10%10,count%10);
		}
		HAL_Delay(15);
		Key_Val=true;
	}
	
	return Key_Val;
}

bool Key1_Read(void)
{
	//uint16_t start_time=0;
	bool Key_Val=false;

	if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_7)==GPIO_PIN_SET){
		HAL_Delay(15);
		while(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_7)==GPIO_PIN_SET){
			Seg_Display(count/100000%10,count/10000%10,count/1000%10,count/100%10,count/10%10,count%10);
		}
		HAL_Delay(15);
		Key_Val=true;
	}

	return Key_Val;
}
uint8_t zhenzhi[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

void Seg_Control(uint16_t Wei,uint16_t Duan)
{
	HAL_GPIO_WritePin(GPIOC,GPIO_DuanXuan,GPIO_PIN_SET);

	uint16_t temp;
	temp=GPIOC->ODR;
	temp&=0x003f;
	temp|=zhenzhi[Duan]<<6;
	GPIOC->ODR=temp;

	HAL_GPIO_WritePin(GPIOG,GPIO_Point,GPIO_PIN_RESET);

	switch(Wei){
		case 0:
			HAL_GPIO_WritePin(GPIOC,Seg_bit0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOG,GPIO_Point,GPIO_PIN_SET);
		break;

		case 1:
			HAL_GPIO_WritePin(GPIOC,Seg_bit1,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOG,GPIO_Point,GPIO_PIN_SET);
		break;

		case 2:
			HAL_GPIO_WritePin(GPIOC,Seg_bit2,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOG,GPIO_Point,GPIO_PIN_SET);
		break;

		case 3:
			HAL_GPIO_WritePin(GPIOC,Seg_bit3,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOG,GPIO_Point,GPIO_PIN_SET);
		break;

		case 4:
			HAL_GPIO_WritePin(GPIOC,Seg_bit4,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOG,GPIO_Point,GPIO_PIN_RESET);
		break;

		case 5:
			HAL_GPIO_WritePin(GPIOC,Seg_bit5,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOG,GPIO_Point,GPIO_PIN_SET);
		break;
	}
}

void Seg_Display(uint16_t a,uint16_t b,uint16_t c,uint16_t d,uint16_t e,uint16_t f)
{
		Seg_Control(0,a);
		HAL_Delay(2);
		Seg_Control(1,b);
		HAL_Delay(2);
		Seg_Control(2,c);
		HAL_Delay(2);
		Seg_Control(3,d);
		HAL_Delay(2);
		Seg_Control(4,e);
		HAL_Delay(2);
		Seg_Control(5,f);
		HAL_Delay(2);
}

void Time_Control(uint64_t Time_Value)
{

    uint8_t hour = (Time_Value / 10000) % 100;
    uint8_t minute = (Time_Value / 100) % 100;
    uint8_t second = Time_Value % 100;


    if (hour >= 24) hour = 0;
    if (minute >= 60) minute = 0;
    if (second >= 60) second = 0;


    while (1)
    {

        uint8_t H0 = hour / 10;
        uint8_t H1 = hour % 10;
        uint8_t M0 = minute / 10;
        uint8_t M1 = minute % 10;
        uint8_t S0 = second / 10;
        uint8_t S1 = second % 10;


        for (int i = 0; i < 83; i++){
            Seg_Display(H0, H1, M0, M1, S0, S1);
        }

        HAL_Delay(2);

        second++;

        if (second >= 60){
            second = 0;
            minute++;
            if (minute >= 60){
                minute = 0;
                hour++;
                if (hour >= 24){
                    hour = 0;
                }
            }
        }
    }
}

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
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		if(Key_Read()){
			count++;
		}
  	if (Key1_Read())
  		count--;
		Seg_Display(count/100000%10, count/10000%10, count/1000%10,count/100%10, count/10%10, count%10);
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
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
