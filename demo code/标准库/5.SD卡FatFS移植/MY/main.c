/***
	***************************************************************************************************
	*	@file  	main.c
	*	@version V1.0
	*	@author  ¹С��Ƽ�	
	*	@brief   SD���ļ�ϵͳ��ֲ��FatFs�汾 R0.13
   ****************************************************************************************************
   *  @description
	*
	*	ʵ��ƽ̨��¹С��STM32F407ZGT6���İ� ���ͺţ�LXB407ZG-P1��
	* �ͷ�΢�ţ�19949278543
	*
>>>>> ����˵����
	*
	*  1.��ֲFatFs�����м򵥵Ĳ���
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
#include "ff.h"


FATFS 	SD_FatFs; 		// �ļ�ϵͳ����
FRESULT 	MyFile_Res;    // ������� 
	
//	������FatFs_Check
//	���ܣ�����FatFs�ļ�ϵͳ�Ĺ���
//
void FatFs_Check(void)	//�ж�FatFs�Ƿ���سɹ�����û�д���FatFs���ʽ��SD��
{
	BYTE work[FF_MAX_SS]; 
	
	MyFile_Res = f_mount(&SD_FatFs,"0:",1);	//����SD��
	
	if (MyFile_Res == FR_OK)	//�ж��Ƿ���سɹ�
	{
		printf("\r\nSD�ļ�ϵͳ���سɹ�\r\n");
	}
	else		
	{
		printf("SD����δ�����ļ�ϵͳ��������ʽ��\r\n");
		
		MyFile_Res = f_mkfs("0:",FM_FAT32,0,work,sizeof work);		//��ʽ��SD����FAT32����Ĭ�ϴ�С16K
		
		if (MyFile_Res == FR_OK)		//�ж��Ƿ��ʽ���ɹ�
			printf("SD����ʽ���ɹ���\r\n");
		else
			printf("��ʽ��ʧ�ܣ���������SD����\r\n");
	}
}
//	������FatFs_GetVolume
//	���ܣ������豸��������������������ʣ������
//
void FatFs_GetVolume(void)	// �����豸����
{
	FATFS *fs;		//����ṹ��ָ��
	u32 SD_CardCapacity = 0;		//SD����������
	u32 SD_FreeCapacity = 0;		//SD����������
	DWORD fre_clust, fre_sect, tot_sect; 	//���дأ���������������������

	f_getfree("0:",&fre_clust,&fs);			//��ȡSD��ʣ��Ĵ�

	tot_sect = (fs->n_fatent-2) * fs->csize;	//���������� = �ܵĴ� * ÿ���ذ�����������
	fre_sect = fre_clust * fs->csize;			//����ʣ��Ŀ���������	   

	SD_CardCapacity = tot_sect / 2048 ;	// SD�������� = �������� * 512( ÿ�������ֽ��� ) / 1048576(�����MB)
	SD_FreeCapacity = fre_sect / 2048 ;	//����ʣ�����������λΪM
	printf("-------------------��ȡ�豸������Ϣ-----------------\r\n");		
	printf("SD������%dMB\r\n",SD_CardCapacity);	
	printf("SDʣ�ࣺ%dMB\r\n",SD_FreeCapacity);
}

//	������FatFs_FileTest
//	���ܣ������ļ�д��Ͷ�ȡ����
//
u8  FatFs_FileTest(void)	//�ļ�������д�����
{
	u8 i = 0;
	u16 BufferSize = 0;	
	FIL	MyFile;			// �ļ�����
	UINT 	MyFile_Num;		//	���ݳ���
	BYTE 	MyFile_WriteBuffer[] = "STM32 SD�� �ļ�ϵͳ����";	//Ҫд�������
	BYTE 	MyFile_ReadBuffer[1024];	//Ҫ����������
	
	printf("-------------FatFs �ļ�������д�����---------------\r\n");
	
	MyFile_Res = f_open(&MyFile,"0:FatFs Test.txt",FA_CREATE_ALWAYS | FA_WRITE);	//���ļ������������򴴽����ļ�
	if(MyFile_Res == FR_OK)
	{
		printf("�ļ���/�����ɹ���׼��д������...\r\n");
		
		MyFile_Res = f_write(&MyFile,MyFile_WriteBuffer,sizeof(MyFile_WriteBuffer),&MyFile_Num);	//���ļ�д������
		if (MyFile_Res == FR_OK)	
		{
			printf("д��ɹ���д������Ϊ��\r\n");
			printf("%s\r\n",MyFile_WriteBuffer);
		}
		else
		{
			printf("�ļ�д��ʧ�ܣ�����SD�������¸�ʽ��!\r\n");
			f_close(&MyFile);	  //�ر��ļ�	
			return ERROR;			
		}
		f_close(&MyFile);	  //�ر��ļ�			
	}
	else
	{
		printf("�޷���/�����ļ�������SD�������¸�ʽ��!\r\n");
		f_close(&MyFile);	  //�ر��ļ�	
		return ERROR;		
	}
	
	printf("-------------FatFs �ļ���ȡ����---------------\r\n");	
	
	BufferSize = sizeof(MyFile_WriteBuffer)/sizeof(BYTE);									// ����д������ݳ���
	MyFile_Res = f_open(&MyFile,"0:FatFs Test.txt",FA_OPEN_EXISTING | FA_READ);	//���ļ������������򴴽����ļ�
	MyFile_Res = f_read(&MyFile,MyFile_ReadBuffer,BufferSize,&MyFile_Num);			// ��ȡ�ļ�
	if(MyFile_Res == FR_OK)
	{
		printf("�ļ���ȡ�ɹ�������У������...\r\n");
		
		for(i=0;i<BufferSize;i++)
		{
			if(MyFile_WriteBuffer[i] != MyFile_ReadBuffer[i])		// У������
			{
				printf("У��ʧ�ܣ�����SD�������¸�ʽ��!\r\n");
				f_close(&MyFile);	  //�ر��ļ�	
				return ERROR;
			}
		}
		printf("У��ɹ�������������Ϊ��\r\n");
		printf("%s\r\n",MyFile_ReadBuffer);
	}	
	else
	{
		printf("�޷���ȡ�ļ�������SD�������¸�ʽ��!\r\n");
		f_close(&MyFile);	  //�ر��ļ�	
		return ERROR;		
	}	
	
	f_close(&MyFile);	  //�ر��ļ�	
	return SUCCESS;
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
	
	FatFs_Check();			//�ж�FatFs�Ƿ���سɹ�����û�д���FatFs���ʽ��SD��
	FatFs_GetVolume();	// �����豸����
	FatFs_FileTest();		//�ļ�������д�����
	
	while (1)
	{
		LED1_Toggle;
		Delay_ms(100);
	}
	
}





