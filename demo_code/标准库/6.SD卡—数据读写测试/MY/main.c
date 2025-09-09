/***
	***************************************************************************************************
	*	@file  	main.c
	*	@version V1.0
	*	@author  ¹С��Ƽ�	
	*	@brief   SD����д����
   ****************************************************************************************************
   *  @description
	*
	*	ʵ��ƽ̨��¹С��STM32F407ZGT6���İ� ���ͺţ�LXB407ZG-P1��
	* �ͷ�΢�ţ�19949278543
	*
>>>>> ����˵����
	*
	*  1.�ڲ���ֲ�ļ�ϵͳ�¶�SD�����м򵥵����ݶ�ȡ����
	* 	2.SD���ײ�������ֲ�ڹٷ�����������
	* 		
	***************************************************************************************************
***/


#include "stm32f4xx.h"
#include "led.h"   
#include "delay.h"
#include "key.h"  
#include "usart.h"
#include "sdio_sd.h"


#define 	SD_BlockSize  512	 //SD�����С

SD_Error	SD_Status ; 		 //SD������־λ
uint8_t 	SD_WriteBuffer[SD_BlockSize];	//	д��������
uint8_t 	SD_ReadBuffer[SD_BlockSize];	//	����������

// ������SD������
//	���ܣ�SD�����д����
//	����ֵ��0 - ��д����ʧ�ܣ�1 - ��д���Գɹ�
//
uint8_t SD_Test(void)
{
	uint16_t i = 0;	
	
	for(i=0;i<SD_BlockSize;i++)	//��Ҫд��SD��������д������
	{
		SD_WriteBuffer[i] = i;
	}
	SD_WriteBlock(SD_WriteBuffer, 0x00, SD_BlockSize);	//��д��
	SD_WaitWriteOperation();						//�ȴ�DMA�������
	while(SD_GetStatus() != SD_TRANSFER_OK);	//�ȴ�ͨ�Ž���
	
	SD_ReadBlock(SD_ReadBuffer, 0x00, SD_BlockSize);	//���ȡ
	SD_WaitReadOperation();							//�ȴ�DMA�������	
	while(SD_GetStatus() != SD_TRANSFER_OK);	//�ȴ�ͨ�Ž���

	for(i=0;i<SD_BlockSize;i++)	//��֤�����������Ƿ����д�������
	{
		if( SD_WriteBuffer[i] != SD_ReadBuffer[i] )	//������ݲ���ȣ��򷵻�0
			return 0;
	}		
	return 1; 	//������ȷ����д����ͨ��������1
}

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
	
	SD_Status = SD_Init();	//SD����ʼ��
	
	if( SD_Status == SD_OK )	//����Ƿ��ʼ���ɹ�
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
		Delay_ms(100);
	}
	
}





