/***
	*************************************************************************************************
	*	@file  	main.c
	*	@version V1.0
	*	@author  ¹С��Ƽ�	
	*	@brief   SD����д����
   *************************************************************************************************
   *  @description
	*
	*	ʵ��ƽ̨��¹С��STM32F103ZET6���İ� ���ͺţ�LXB103ZE-P1��
	* �ͷ�΢�ţ�19949278543
	*
>>>>> ����˵����
	*
	*  1. ʹ��SDIO�ӿ���SD������ͨ�ţ����м򵥵Ķ�д����
	* 	2. �����ļ���ֲ�� STM32429-EVAL �忨������
	*
	*************************************************************************************************
***/
#include "main.h"
#include "led.h"   
#include "key.h"
#include "usart.h"
#include "sdio_sd.h"

/********************************************** �������� *******************************************/

#define 	Test_BlockSize  ((BLOCKSIZE * NumOf_Blocks) >> 2)	 //�������ݴ�С,SD���СΪ512�ֽڣ���Ϊ��32λ�����飬�����������4
#define	Test_Addr 	 0x00
#define	NumOf_Blocks	1

uint8_t SD_Status ; 		 //SD������־λ
uint32_t SD_WriteBuffer[Test_BlockSize];	//	д��������
uint32_t SD_ReadBuffer[Test_BlockSize];	//	����������

/********************************************** �������� *******************************************/


// ������SD������
//	���ܣ�SD�����д����
//	����ֵ��0 - ��д����ʧ�ܣ�1 - ��д���Գɹ�
//
uint8_t SD_Test(void)
{
	uint32_t i = 0;	
	
	for(i=0;i<Test_BlockSize;i++)	//��Ҫд��SD��������д������
	{
		SD_WriteBuffer[i] = i+3;
	}
	
	BSP_SD_Erase(Test_Addr, NumOf_Blocks);
	while(BSP_SD_GetCardState() != SD_TRANSFER_OK);	//�ȴ�ͨ�Ž���
	
	BSP_SD_WriteBlocks_DMA(SD_WriteBuffer, Test_Addr, NumOf_Blocks);	//��д��
	while(BSP_SD_GetCardState() != SD_TRANSFER_OK);	//�ȴ�ͨ�Ž���
	
	BSP_SD_ReadBlocks_DMA(SD_ReadBuffer, Test_Addr, NumOf_Blocks);	//���ȡ
	while(BSP_SD_GetCardState() != SD_TRANSFER_OK);	//�ȴ�ͨ�Ž���

	for(i=0;i<Test_BlockSize;i++)	//��֤�����������Ƿ����д�������
	{
		if( SD_WriteBuffer[i] != SD_ReadBuffer[i] )	//������ݲ���ȣ��򷵻�0
			return 0;
	}		
	return 1; 	//������ȷ����д����ͨ��������1
}


void SystemClock_Config(void);		// ϵͳʱ������

/***************************************************************************************************
*	�� �� ��: main

*	��������: ������

****************************************************************************************************/

int main(void)
{
	HAL_Init();					// ��ʼ��HAL��	
	SystemClock_Config();   // ����ϵͳʱ�ӣ���Ƶ180MHz
	LED_Init();             // ��ʼ��LED����
	KEY_Init();					// ��ʼ����������
	USART1_Init();				// USART1��ʼ��

	SD_Status = BSP_SD_Init();	//SD����ʼ��
	
	if( SD_Status == MSD_OK )	//����Ƿ��ʼ���ɹ�
	{		
		printf("SD����ʼ���ɹ� \r\n");	
		
		if( SD_Test() == 1 )		//SD����д����
			printf("SD�� Block ��д�ɹ� \r\n");	
		else
			printf("��дʧ�ܣ������SD�� \r\n");			
	}
	else
		printf("\r\n ��ⲻ��SD�� \r\n");	

  while (1)
  {
		LED1_Toggle;
		HAL_Delay(150);  
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
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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

