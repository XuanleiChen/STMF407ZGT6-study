/***
	*************************************************************************************************
	*	@file  	main.c
	*	@version V1.0
	*	@author  ¹С��Ƽ�
	*	@brief   RTCʵ��
   ************************************************************************************************
   *  @description
	*
	*	ʵ��ƽ̨��¹С��STM32F103ZET6���İ� ���ͺţ�LXB103ZE-P1��
	* �ͷ�΢�ţ�19949278543
	*
>>>>> ����˵����
	*
	*	1.��ʼ��RTC��ȡʱ�������
	*	2.ͨ�����ڴ�ӡʱ����Ϣ�����ڲ�����115200��ʹ��USART1��PA9/PA10
	*
	************************************************************************************************
***/

#include "main.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "rtc.h"


//********************************************** �������� *******************************************/

extern RTC_HandleTypeDef hrtc;	// RTC���

RTC_TimeTypeDef Time_Struct;		// ����
RTC_DateTypeDef Date_Struct;		// ʱ��



/********************************************** �������� *******************************************/

void SystemClock_Config(void);		// ʱ�ӳ�ʼ��

/***************************************************************************************************
*	�� �� ��: main
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: ����������
*	˵    ��: ��
****************************************************************************************************/

int main(void)
{
	HAL_Init();					// ��ʼ��HAL��
	SystemClock_Config();	// ����ϵͳʱ��
	LED_Init();					// ��ʼ��LED����
	USART1_Init();				// USART1��ʼ��	

	MX_RTC_Init();				// RTC��ʼ��
	
	printf("STM32 RTC ���� \r\n");

	while (1)
	{
		HAL_RTC_GetTime(&hrtc,&Time_Struct,RTC_FORMAT_BIN);	// ��ȡʱ��

//		STM32��RTCΪȷ���� ���롢ʱ�䡢���� 3��ֵ����ͬһʱ�̵㣬
//		��ȡ ���루RTC_SSR ���� ʱ�䣨RTC_TR ��ʱ�������߽�Ӱ�ӼĴ����е�ֵ��ֱ����ȡRTC_DR��	
//		Ҳ����˵�û��������ڵĻ���ʱ��ֵ�ᱻ����	
		HAL_RTC_GetDate(&hrtc,&Date_Struct,RTC_FORMAT_BIN);	// ��ȡ����
		
		printf("%d-%d-%d ",Date_Struct.Year+2000,Date_Struct.Month,Date_Struct.Date);
		printf("%d:%d:%d\r\n",Time_Struct.Hours,Time_Struct.Minutes,Time_Struct.Seconds);

		HAL_Delay(1000);
		LED1_Toggle;
	}

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  
  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
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
  
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  
}

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
