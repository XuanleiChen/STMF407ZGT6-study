/***
	***************************************************************************************************
	*	@file  	main.c
	*	@version V1.0
	*	@author  ¹С��Ƽ�	
	*	@brief   RTC��ȡʱ��
   ****************************************************************************************************
   *  @description
	*
	*	ʵ��ƽ̨��¹С��STM32F407ZGT6���İ� ���ͺţ�LXB407ZG-P1��
	* �ͷ�΢�ţ�19949278543
	*
>>>>> ����˵����
	*
	*	��ȡʱ�䣬ͨ�����ڴ�ӡ��PC
	* 		
	***************************************************************************************************
***/


#include "stm32f4xx.h"
#include "led.h"   
#include "delay.h"
#include "key.h"  
#include "usart.h"
#include "rtc.h" 

RTC_TimeTypeDef Time_Struct;		// ʱ��
RTC_DateTypeDef Date_Struct;		//	����


/***************************************************************************************************
*	�� �� ��: main
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: ����������
*	˵    ��: ��
****************************************************************************************************/

int main(void)
{
		
	Delay_Init();		//��ʱ������ʼ��
	LED_Init();			//LED��ʼ��
	KEY_Init();			//����IO�ڳ�ʼ��
	Usart_Config ();	// USART��ʼ������
	
	RTC_Initialize();			// ��ʼ��RTC

	printf("STM32 RTC��ȡ\r\n");	
	
	while (1)
	{		
		RTC_GetTime(RTC_Format_BIN,&Time_Struct);	 // ��ȡʱ����
		RTC_GetDate(RTC_Format_BIN,&Date_Struct);	 // ��ȡ������
		printf("%d-%d-%d ",Date_Struct.RTC_Year+2000,Date_Struct.RTC_Month,Date_Struct.RTC_Date);			// ��ӡ������
		printf("%d:%d:%d\r\n",Time_Struct.RTC_Hours,Time_Struct.RTC_Minutes,Time_Struct.RTC_Seconds);	// ��ӡʱ����
		LED1_Toggle;			// LED��˸
		Delay_ms(999);		
	}
	
}





