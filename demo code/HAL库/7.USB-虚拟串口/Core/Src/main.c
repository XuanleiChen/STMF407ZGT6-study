/***
	*************************************************************************************************
	*	@file  	main.c
	*	@version V1.0
	*	@author  ¹С��Ƽ�
	*	@brief   USB ���⴮�ڴ�ӡ����
   ************************************************************************************************
   *  @description
	*
	*	ʵ��ƽ̨��¹С��STM32F103ZET6���İ� ���ͺţ�LXB103ZE-P1��
	* �ͷ�΢�ţ�19949278543
	*
>>>>> ����˵����
	*
	*	1.USB���⴮�ڴ�ӡ����
	*	2.��Type-C�����߲�����İ��Type-C�ڣ��򿪴������ּ��ɽ������ݣ��������ò�����
	*
	************************************************************************************************
***/

#include "main.h"
#include "led.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"


/********************************************** �������� *******************************************/

uint8_t  a[] = {	
	
"!#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\r\n\
!#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\r\n\
!#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\r\n\
!#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\r\n\
!#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\r\n\
!#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\r\n\
!#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\r\n\
"
} ;   

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

	MX_USB_DEVICE_Init();	// USB�豸��ʼ��

	// ��Ƭ���͵��Խ���USB������Ҫһ����ʱ�䣬�����ϵ�֮���ӡ���������׶�ʧ���û��ɼ��ʵ���ʱ
	USB_printf("STM32F103���⴮��ʵ��\r\n");	
	USB_printf("��ӡ����>>>>>>\r\n"); 
	
	while (1)
	{
		USB_printf(">>>\r\n%s\r\n",a);
		LED1_Toggle;
		HAL_Delay(500);
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

