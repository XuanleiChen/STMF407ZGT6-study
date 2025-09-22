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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "keys.h"
#include "oled.h"
#include "delay.h"

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
uint8_t display_mode;//显示模式 0-省 1-市
int8_t cursor1;//光标
int8_t cursor2;//光标

uint8_t display_mode_old;
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
  //Delay_Init();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */

  /* USER CODE BEGIN 2 */
	OLED_Init();
	Keys_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
	
	
  while (1)
  {
		
		if(KeyA0_HasBeenClicked()){
			cursor2=0;
			display_mode++;
		}
		if(KeyA1_HasBeenClicked()){
			cursor2=0;
			display_mode=0;
		}
		
		if(display_mode>1){
			display_mode=0;
		}

		
		if(KeyA1_HasBeenClicked()){//强制返回主界面
			display_mode=0;
		}
		switch(display_mode){
			case 0://省模式
				if(KeyB0_HasBeenClicked()){
					cursor1++;
				}
				if(KeyB1_HasBeenClicked()){
					cursor1--;
				}
				if(cursor1>3){//光标越界检测
					cursor1=0;
				}else if(cursor1<0){
					cursor1=3;
				}
				
				OLED_ShowChinese(1,8,"山东省");
				OLED_ShowChinese(2,8,"山西省");
				OLED_ShowChinese(3,8,"湖北省"); 
				OLED_ShowChinese(4,8,"四川省");

				switch(cursor1){//光标的移动与闪烁,行标识符的移动切换 
					case 0:
						OLED_ShowChinese(1,5,"●");
						OLED_ShowChinese(2,5,"○");
						OLED_ShowChinese(3,5,"○");
						OLED_ShowChinese(4,5,"○");
					
						OLED_ShowString(4,1,"   ");
						OLED_ShowChinese(1,1,"→");
						HAL_Delay(250);
						OLED_ShowString(1,1,"   ");
						HAL_Delay(250);
					break;
					
					case 1:
						OLED_ShowChinese(1,5,"○");
						OLED_ShowChinese(2,5,"●");
						OLED_ShowChinese(3,5,"○");
						OLED_ShowChinese(4,5,"○");
					
						OLED_ShowString(1,1,"   ");
						OLED_ShowChinese(2,1,"→");
						HAL_Delay(250);
						OLED_ShowString(2,1,"   ");
						HAL_Delay(250);
					break;
					
					case 2:
						OLED_ShowChinese(1,5,"○");
						OLED_ShowChinese(2,5,"○");
						OLED_ShowChinese(3,5,"●");
						OLED_ShowChinese(4,5,"○");
					
						OLED_ShowString(2,1,"   ");
						OLED_ShowChinese(3,1,"→");
						HAL_Delay(250);
						OLED_ShowString(3,1,"   ");
						HAL_Delay(250);
					break;
					
					case 3:
						OLED_ShowChinese(1,5,"○");
						OLED_ShowChinese(2,5,"○");
						OLED_ShowChinese(3,5,"○");
						OLED_ShowChinese(4,5,"●");
					
						OLED_ShowString(3,1,"   ");
						OLED_ShowChinese(4,1,"→");
						HAL_Delay(250);
						OLED_ShowString(4,1,"   ");
						HAL_Delay(250);
					break;
				}
				break;

			case 1://市模式

					switch (cursor1){//根据不同的省份显示地级市 
						case 0://山东
							OLED_ShowChinese(1,8,"济南市");
							OLED_ShowChinese(2,8,"青岛市");
							OLED_ShowChinese(3,8,"烟台市");
							OLED_ShowChinese(4,8,"淄博市");
						break;
						
						case 1://山西
							OLED_ShowChinese(1,8,"太原市");
							OLED_ShowChinese(2,8,"吕梁市");
							OLED_ShowChinese(3,8,"长治市");
							OLED_ShowChinese(4,8,"晋中市");
						break;
						
						case 2://湖北
							
							OLED_ShowChinese(1,8,"武汉市");
							OLED_ShowChinese(2,8,"宜昌市");
							OLED_ShowChinese(3,8,"襄阳市");
							OLED_ShowChinese(4,8,"荆州市");
						break;
						
						case 3://四川
							OLED_ShowChinese(1,8,"成都市");
							OLED_ShowChinese(2,8,"绵阳市");
							OLED_ShowChinese(3,8,"宜宾市");
							OLED_ShowChinese(4,8,"德阳市");
						break;
					
				}
			
				if(KeyB0_HasBeenClicked()){//光标移动
					cursor2++;
				}
				if(KeyB1_HasBeenClicked()){
					cursor2--;
				}
				if(cursor2>3){//光标越界检测
					cursor2=0;
				}else if(cursor2<0){
					cursor2=3;
				}
				
				switch(cursor2){//光标的移动与闪烁,行标识符的移动切换 
					case 0:
						OLED_ShowChinese(1,5,"●");
						OLED_ShowChinese(2,5,"○");
						OLED_ShowChinese(3,5,"○");
						OLED_ShowChinese(4,5,"○");
					
						OLED_ShowString(4,1,"   ");
						OLED_ShowChinese(1,1,"→");
						HAL_Delay(250);
						OLED_ShowString(1,1,"   ");
						HAL_Delay(250);
					break;
					
					case 1:
						OLED_ShowChinese(1,5,"○");
						OLED_ShowChinese(2,5,"●");
						OLED_ShowChinese(3,5,"○");
						OLED_ShowChinese(4,5,"○");
					
						OLED_ShowString(1,1,"   ");
						OLED_ShowChinese(2,1,"→");
						HAL_Delay(250);
						OLED_ShowString(2,1,"   ");
						HAL_Delay(250);
					break;
					
					case 2:
						OLED_ShowChinese(1,5,"○");
						OLED_ShowChinese(2,5,"○");
						OLED_ShowChinese(3,5,"●");
						OLED_ShowChinese(4,5,"○");
					
						OLED_ShowString(2,1,"   ");
						OLED_ShowChinese(3,1,"→");
						HAL_Delay(250);
						OLED_ShowString(3,1,"   ");
						HAL_Delay(250);
					break;
					
					case 3:
						OLED_ShowChinese(1,5,"○");
						OLED_ShowChinese(2,5,"○");
						OLED_ShowChinese(3,5,"○");
						OLED_ShowChinese(4,5,"●");
					
						OLED_ShowString(3,1,"   ");
						OLED_ShowChinese(4,1,"→");
						HAL_Delay(250);
						OLED_ShowString(4,1,"   ");
						HAL_Delay(250);
					break;
				}

				
			break;
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

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
#ifdef USE_FULL_ASSERT
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
