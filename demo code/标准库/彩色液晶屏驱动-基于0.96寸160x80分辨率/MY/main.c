/***
	***************************************************************************************************
	*	@file  	main.c
	*	@version V1.0
	*	@author  ¹С��Ƽ�	
	*	@brief   SPI������ʾ������Ļ������ ST7789
   ****************************************************************************************************
   *  @description
	*
	*	ʵ��ƽ̨��¹С��STM32F407ZGT6���İ� ���ͺţ�LXB407ZG-P1��
	* �ͷ�΢�ţ�19949278543
   *
>>>>> ����˵����
	*
	*	1. �����ֿ�ʹ�õ���С�ֿ⣬���õ��˶�Ӧ�ĺ�����ȥȡģ���û����Ը����������������ɾ��
	*	2. ���������Ĺ��ܺ�ʹ�ÿ��Բο�������˵��
	*
	***************************************************************************************************
***/


#include "stm32f4xx.h"
#include "led.h"   
#include "delay.h"
#include "key.h"  
#include "usart.h"
#include "lcd_spi_096.h"

// LCD���Ժ��������������ڵײ�
void 	LCD_Test_Clear(void);			// ��������
void 	LCD_Test_Text(void);			   // �ı�����
void 	LCD_Test_Variable (void);	   // ������ʾ������������С��
void 	LCD_Test_Color(void);			// ����������
void 	LCD_Test_Grahic(void);		   // 2Dͼ�λ���
void 	LCD_Test_Image(void);			// ͼƬ��ʾ
void  LCD_Test_Direction(void);	   // ������ʾ����


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
	
	SPI_LCD_Init();	// LCD��ʼ��

	while (1)
	{
		LCD_Test_Clear(); 		// ��������
		LCD_Test_Text();			// �ı�����
		LCD_Test_Variable();		// ������ʾ������������С��
		LCD_Test_Color();			// ��ɫ����
		LCD_Test_Grahic();		// 2Dͼ�λ���	
		LCD_Test_Image();			// ͼƬ��ʾ
		LCD_Test_Direction();	// ������ʾ����	
	}
}


/*************************************************************************************************
*	�� �� ��:	LCD_Test_Clear
*
*	��������:	��������
*************************************************************************************************/
void LCD_Test_Clear(void)
{
	uint8_t	i = 0;			// ��������
	
	LCD_SetDirection(Direction_H_Flip);		
	LCD_SetTextFont(&CH_Font16);			// ����2424��������,ASCII�����ӦΪ2412
	LCD_SetColor(LCD_BLACK);				// ���û�����ɫ

	for(i=0;i<8;i++)
	{
		switch (i)		// �л�����ɫ
		{
			case 0: LCD_SetBackColor(LIGHT_RED); 		break;	
			case 1: LCD_SetBackColor(LIGHT_GREEN); 	break;				
			case 2: LCD_SetBackColor(LIGHT_BLUE); 		break;
			case 3: LCD_SetBackColor(LIGHT_YELLOW); 	break;
			case 4: LCD_SetBackColor(LIGHT_CYAN);		break;
			case 5: LCD_SetBackColor(LIGHT_GREY); 		break;
			case 6: LCD_SetBackColor(LIGHT_MAGENTA); 	break;
			case 7: LCD_SetBackColor(LCD_WHITE); 		break;			
			default:	break;			
		}
		LCD_Clear();		// ����
		LCD_DisplayText(13, 5,"STM32 ˢ������");
		LCD_DisplayText(13,30,"��Ļ�ֱ���:160*80");
		LCD_DisplayText(13,55,"������:ST7735");	
		Delay_ms(1000);	// ��ʱ
	}
}

/*************************************************************************************************
*	�� �� ��:	LCD_Test_Text
*
*	��������:	�ı���ʾ����
*
*	˵    ��:	��ʾ�ı����������������С�����ĺ�ASCII�ַ� 
*************************************************************************************************/
void LCD_Test_Text(void)
{
	LCD_SetBackColor(LCD_BLACK); 			//	���ñ���ɫ
	LCD_Clear(); 								// ����

	LCD_SetColor(LCD_CYAN);   
	LCD_SetAsciiFont(&ASCII_Font12); LCD_DisplayString(0,  0,"ASCII:12*12"); 	
	LCD_SetAsciiFont(&ASCII_Font16); LCD_DisplayString(0, 12,"ASCII:16*16");																																		                                                                   					  		
	LCD_SetAsciiFont(&ASCII_Font20); LCD_DisplayString(0, 28,"ASCII:20*20");  
	LCD_SetColor(LCD_WHITE);				    		
	LCD_SetAsciiFont(&ASCII_Font24); LCD_DisplayString(0, 48,"ASCII:2424"); 
	LCD_SetColor(LCD_YELLOW);		
	LCD_SetAsciiFont(&ASCII_Font32); LCD_DisplayString(135, 25,"*");
	LCD_SetAsciiFont(&ASCII_Font32); LCD_DisplayString(128,  0,"32"); LCD_DisplayString(128,  48,"32");

	Delay_ms(2000);	// ��ʱ�ȴ�
	LCD_Clear(); 								// ����

	LCD_SetTextFont(&CH_Font12);			// ����1212��������,ASCII�����ӦΪ1206
	LCD_SetColor(0X8AC6D1);					// ���û���
	LCD_DisplayText(0, 0,"1212:¹С��Ƽ�");	
	
	LCD_SetTextFont(&CH_Font16);			// ����1616��������,ASCII�����ӦΪ1608
	LCD_SetColor(0XC5E1A5);					// ���û���
	LCD_DisplayText(0, 12,"1616:¹С��Ƽ�");		
	
	LCD_SetTextFont(&CH_Font20);			// ����2020��������,ASCII�����ӦΪ2010
	LCD_SetColor(0XFFB549);					// ���û���
	LCD_DisplayText(0, 28,"2020:¹С��Ƽ�");		

	LCD_SetTextFont(&CH_Font24);			// ����2424��������,ASCII�����ӦΪ2412
	LCD_SetColor(0XFF585D);					// ���û���
	LCD_DisplayText(0, 48,"2424:¹С��Ƽ�");		

	Delay_ms(2000);	// ��ʱ�ȴ�
}

/************************************************************************************************
*	�� �� ��:	LCD_Test_Variable
*
*	��������:	������ʾ������������С��
*************************************************************************************************/
void LCD_Test_Variable (void)
{
	uint16_t i;					// ��������
	int32_t	a = 0;			// �����������������ڲ���
	int32_t	b = 0;			// �����������������ڲ���
	int32_t	c = 0;			// �����������������ڲ���

	double f = -1234.1234;	// ���帡�������������ڲ���
	
	LCD_SetBackColor(LCD_BLACK); 			//	���ñ���ɫ
	LCD_Clear(); 								// ����
	
   LCD_SetTextFont(&CH_Font16);     
	LCD_SetColor(LIGHT_CYAN);					// ���û��ʣ�����ɫ	

	LCD_DisplayText(0, 0,"����:");									
				
	LCD_SetColor(LIGHT_YELLOW);				// ���û��ʣ�����ɫ		
	LCD_DisplayText(0,20,"���ո�:");	
	LCD_DisplayText(0,40,"���0:");	
	
	LCD_SetColor(LIGHT_RED);					// ���û���	������ɫ		
	LCD_DisplayText(0,60,"С��:");	

	
	for(i=0;i<100;i++)
   {
		LCD_SetColor(LIGHT_CYAN);								// ���û���	������ɫ	
		LCD_ShowNumMode(Fill_Space);							// ����λ���ո�
		LCD_DisplayNumber( 50,0, b+i*10, 4) ;				// ��ʾ����			
		LCD_DisplayNumber( 100,0, c-i*10, 4) ;				// ��ʾ����			
		
		LCD_SetColor(LIGHT_YELLOW);								// ���û��ʣ�����ɫ	

		LCD_ShowNumMode(Fill_Space);								// ����λ��� �ո�
		LCD_DisplayNumber( 80,20, a+i*150, 8) ;				// ��ʾ����		

		LCD_ShowNumMode(Fill_Zero);								// ����λ���0      
		LCD_DisplayNumber( 80,40, b+i*150, 8) ;				// ��ʾ����			
		
		LCD_SetColor(LIGHT_RED);									// ���û��ʣ�����ɫ			
		LCD_ShowNumMode(Fill_Space);								// ����λ���ո�		
		LCD_DisplayDecimals( 50,60, f+i*0.01, 11,4);		// ��ʾС��		
		
		Delay_ms(15);				
   }
	Delay_ms(2500);		
}
/*************************************************************************************************
*	�� �� ��:	LCD_Test_Color
*
*	��������:	��ɫ��
*************************************************************************************************/
void LCD_Test_Color(void)
{
	uint16_t i;					// ��������
	uint16_t y;
// ��ɫ����>>>>>	
	LCD_SetBackColor(LCD_BLACK); //���ñ���ɫ
	LCD_Clear(); //������ˢ����ɫ
	
	LCD_SetTextFont(&CH_Font16);			// ��������
	LCD_SetColor(LCD_WHITE);				// ���û�����ɫ
	LCD_DisplayText(0,0,"RGB����ɫ:");

	//ʹ�û��ߺ�����������ɫɫ��
	for(i=0;i<160;i++)
	{
		LCD_SetColor( LCD_RED-(i<<16) );
      LCD_DrawLine_V(0+i,  20,10);
	}
	for(i=0;i<240;i++)
	{
		LCD_SetColor( LCD_GREEN-(i<<8) );
      LCD_DrawLine_V(0+i,  30,10);
	}
	for(i=0;i<240;i++)
	{
		LCD_SetColor( LCD_BLUE-i );
      LCD_DrawLine_V(0+i,  40,10);
	}	

   y = 50;
   LCD_SetColor(LIGHT_CYAN);    LCD_FillRect(85,y+5     ,75,10);  LCD_DisplayString(0,y     ,"LIGHT_CYAN");	   
	LCD_SetColor(LIGHT_MAGENTA); LCD_FillRect(105,y+16*1+5,55,10);  LCD_DisplayString(0,y+16*1,"LIGHT_MAGENTA");	

	Delay_ms(2000);
}

/*************************************************************************************************
*	�� �� ��:	LCD_Test_Grahic
*
*	��������:	2Dͼ�λ���
*************************************************************************************************/
void LCD_Test_Grahic(void)
{
	LCD_SetBackColor(LCD_BLACK); //���ñ���ɫ
	LCD_Clear(); //������ˢ����ɫ	

	LCD_SetColor(LCD_WHITE);	
	LCD_DrawRect(0,0,160,80); 			//���ƾ���

	LCD_SetColor(LCD_RED);    LCD_FillCircle(50,40,30);		//���Բ��
	LCD_SetColor(LCD_GREEN);  LCD_FillCircle(80,40,30); 	
	LCD_SetColor(LCD_BLUE);   LCD_FillCircle(110,40,30);  	
	
	Delay_ms(1000);	
	LCD_Clear(); //������ˢ����ɫ	
	
	LCD_SetColor(LIGHT_CYAN);
	LCD_DrawCircle(80,40,30);			//����Բ��
	LCD_DrawCircle(80,40,20);   

	LCD_SetColor(LIGHT_RED);	
	LCD_DrawEllipse(80,40,70,28); 	//������Բ 
	LCD_DrawEllipse(80,40,60,35); 	//������Բ    

	Delay_ms(1000);		
}
/*************************************************************************************************
*	�� �� ��:	LCD_Test_Image
*
*	��������:	ͼƬ��ʾ����
*************************************************************************************************/
void LCD_Test_Image(void)
{
	LCD_SetBackColor(LCD_BLACK); 			//	���ñ���ɫ
	LCD_Clear(); 								// ����
	
	LCD_SetColor( 0xffF6E58D);
	LCD_DrawImage( 10, 10, 60, 60, Image_Android_60x60) ;	   // ��ʾͼƬ

	LCD_SetColor( 0xff9DD3A8);
	LCD_DrawImage( 90, 10, 60, 60, Image_Toys_60x60) ;		// ��ʾͼƬ

	Delay_ms(2000);	
}
/*************************************************************************************************
*	�� �� ��:	LCD_Test_Direction
*
*	��������:	������ʾ����
*************************************************************************************************/
void  LCD_Test_Direction(void)
{
   LCD_SetDirection(Direction_V);		   
	LCD_SetBackColor(LCD_BLACK); 			//	���ñ���ɫ
	LCD_Clear(); 								// ����
	LCD_SetTextFont(&CH_Font12);  
	LCD_SetColor( 0xffDFF9FB);  	
	LCD_DisplayText(5,10,"Direction_V"); 	
	LCD_SetColor( 0xffF6E58D);
	LCD_DrawImage( 10,50, 60, 60, Image_Android_60x60) ;	   // ��ʾͼƬ
	LCD_SetTextFont(&CH_Font24);
	LCD_SetColor( 0xff9DD3A8);  
	LCD_DisplayText(16,112,"¹С��");
	LCD_DisplayText(16,136,"�Ƽ�");
	Delay_ms(1000);	// ��ʱ	

   LCD_SetDirection(Direction_H);		   
	LCD_SetBackColor(LCD_BLACK); 			//	���ñ���ɫ
	LCD_Clear(); 								// ����
	LCD_SetTextFont(&CH_Font16);  
	LCD_SetColor( 0xffDFF9FB);  	
	LCD_DisplayText(20,0,"Direction_H"); 	
	LCD_SetColor( 0xffF6E58D);
	LCD_DrawImage( 30,20, 60, 60, Image_Android_60x60) ;	   // ��ʾͼƬ
	LCD_SetTextFont(&CH_Font24);
	LCD_SetColor( 0xff9DD3A8);  
	LCD_DisplayText(100,16,"¹С��");
	LCD_DisplayText(100,40,"�Ƽ�");
	Delay_ms(1000);	// ��ʱ		

   LCD_SetDirection(Direction_V_Flip);		   
	LCD_SetBackColor(LCD_BLACK); 			//	���ñ���ɫ
	LCD_Clear(); 								// ����
	LCD_SetTextFont(&CH_Font16);  
	LCD_SetColor( 0xffDFF9FB);  	
	LCD_DisplayText(20,10,"_V_Flip"); 	
	LCD_SetColor( 0xffF6E58D);
	LCD_DrawImage( 10,50, 60, 60, Image_Android_60x60) ;	   // ��ʾͼƬ
	LCD_SetTextFont(&CH_Font24);
	LCD_SetColor( 0xff9DD3A8);  
	LCD_DisplayText(16,112,"¹С��");
	LCD_DisplayText(16,136,"�Ƽ�");
	Delay_ms(1000);	// ��ʱ		

   LCD_SetDirection(Direction_H_Flip);		   
	LCD_SetBackColor(LCD_BLACK); 			//	���ñ���ɫ
	LCD_Clear(); 								// ����
	LCD_SetTextFont(&CH_Font16);  
	LCD_SetColor( 0xffDFF9FB);  	
	LCD_DisplayText(20,0,"Direction_H_Flip"); 	
	LCD_SetColor( 0xffF6E58D);
	LCD_DrawImage( 30,20, 60, 60, Image_Android_60x60) ;	   // ��ʾͼƬ
	LCD_SetTextFont(&CH_Font24);
	LCD_SetColor( 0xff9DD3A8);  
	LCD_DisplayText(100,16,"¹С��");
	LCD_DisplayText(100,40,"�Ƽ�");
	Delay_ms(1000);	// ��ʱ		

}

