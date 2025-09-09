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
#include "lcd_spi_114.h"

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
	LCD_SetTextFont(&CH_Font24);			// ����2424��������,ASCII�����ӦΪ2412
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
		LCD_DisplayText(13, 20,"STM32 ˢ������");
		LCD_DisplayText(13,56,"��Ļ�ֱ���:240*135");
		LCD_DisplayText(13,92,"������:ST7789");	
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
	
	LCD_SetColor(LCD_WHITE);
	LCD_SetAsciiFont(&ASCII_Font32); LCD_DisplayString(0,  0,"!#$'()*+,-.0123"); 						    		
	LCD_SetAsciiFont(&ASCII_Font24); LCD_DisplayString(0, 32,"!#$'()*+,-.012345678"); 
	LCD_SetColor(LCD_CYAN);   
	LCD_SetAsciiFont(&ASCII_Font20); LCD_DisplayString(0, 56,"!#$'()*+,-.0123456789:;<");      	
	LCD_SetAsciiFont(&ASCII_Font16); LCD_DisplayString(0, 76,"!#$'()*+,-.0123456789:;<=>?@AB"); 	
	LCD_SetAsciiFont(&ASCII_Font12); LCD_DisplayString(0, 92,"!#$'()*+,-.0123456789:;<=>?@ABCDEFGHIJKL"); 	
																																		                                                                   					  		
	LCD_SetTextFont(&CH_Font24);			// ����2424��������,ASCII�����ӦΪ2412
	LCD_SetColor(LCD_YELLOW);				// ���û��ʣ���ɫ
	LCD_DisplayText(0, 111,"ASCII�ַ���");

	Delay_ms(2000);	// ��ʱ�ȴ�
	LCD_Clear(); 								// ����

	LCD_SetTextFont(&CH_Font12);			// ����1212��������,ASCII�����ӦΪ1206
	LCD_SetColor(0X8AC6D1);					// ���û���
	LCD_DisplayText(14, 0,"1212:¹С��Ƽ�");	
	
	LCD_SetTextFont(&CH_Font16);			// ����1616��������,ASCII�����ӦΪ1608
	LCD_SetColor(0XC5E1A5);					// ���û���
	LCD_DisplayText(14, 12,"1616:¹С��Ƽ�");		
	
	LCD_SetTextFont(&CH_Font20);			// ����2020��������,ASCII�����ӦΪ2010
	LCD_SetColor(0XFFB549);					// ���û���
	LCD_DisplayText(14, 28,"2020:¹С��Ƽ�");		

	LCD_SetTextFont(&CH_Font24);			// ����2424��������,ASCII�����ӦΪ2412
	LCD_SetColor(0XFF585D);					// ���û���
	LCD_DisplayText(14, 48,"2424:¹С��Ƽ�");		

	LCD_SetTextFont(&CH_Font32);			// ����3232��������,ASCII�����ӦΪ3216
	LCD_SetColor(0xFFB6B9);					// ���û���
	LCD_DisplayText(14, 72,"3232:¹С��Ƽ�");		

	LCD_SetTextFont(&CH_Font24);			// ����2424��������,ASCII�����ӦΪ2412
	LCD_SetColor(LCD_WHITE);
 	LCD_DisplayText(14,103,"������ʾ");	  

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

	double p = 3.1415926;	// ���帡�������������ڲ���
	double f = -1234.1234;	// ���帡�������������ڲ���
	
	LCD_SetBackColor(LCD_BLACK); 			//	���ñ���ɫ
	LCD_Clear(); 								// ����
	
   LCD_SetTextFont(&CH_Font24);     
	LCD_SetColor(LIGHT_CYAN);					// ���û��ʣ�����ɫ		
	LCD_DisplayText(0, 0,"����:");				
	LCD_DisplayText(0,22,"����:");					
				
	LCD_SetColor(LIGHT_YELLOW);				// ���û��ʣ�����ɫ		
	LCD_DisplayText(0,44,"���ո�:");	
	LCD_DisplayText(0,66,"���0:");	
	
	LCD_SetColor(LIGHT_RED);					// ���û���	������ɫ		
	LCD_DisplayText(0,88,"��С��:");	
	LCD_DisplayText(0,110,"��С��:");		
	
	for(i=0;i<100;i++)
   {
		LCD_SetColor(LIGHT_CYAN);								// ���û���	������ɫ	
		LCD_ShowNumMode(Fill_Space);							// ����λ���ո�
		LCD_DisplayNumber( 80,0, b+i*10, 4) ;				// ��ʾ����			
		LCD_DisplayNumber( 80,22, c-i*10, 4) ;				// ��ʾ����			
		
		LCD_SetColor(LIGHT_YELLOW);								// ���û��ʣ�����ɫ	

		LCD_ShowNumMode(Fill_Space);								// ����λ��� �ո�
		LCD_DisplayNumber( 130,44, a+i*150, 8) ;				// ��ʾ����		

		LCD_ShowNumMode(Fill_Zero);								// ����λ���0      
		LCD_DisplayNumber( 130,66, b+i*150, 8) ;				// ��ʾ����			
		
		LCD_SetColor(LIGHT_RED);									// ���û��ʣ�����ɫ			
		LCD_ShowNumMode(Fill_Space);								// ����λ���ո�		
		LCD_DisplayDecimals( 100, 88, p+i*0.1,  6,3);		// ��ʾС��	
		LCD_DisplayDecimals( 100,110, f+i*0.01, 11,4);		// ��ʾС��		
		
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
	
	LCD_SetTextFont(&CH_Font20);			// ��������
	LCD_SetColor(LCD_WHITE);				// ���û�����ɫ
	LCD_DisplayText(0,0,"RGB����ɫ:");

	//ʹ�û��ߺ�����������ɫɫ��
	for(i=0;i<240;i++)
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
   LCD_SetColor(LIGHT_CYAN);    LCD_FillRect(150,y+5     ,90,10);  LCD_DisplayString(0,y     ,"LIGHT_CYAN");	   
	LCD_SetColor(LIGHT_MAGENTA); LCD_FillRect(150,y+20*1+5,90,10);  LCD_DisplayString(0,y+20*1,"LIGHT_MAGENTA");	
	LCD_SetColor(LIGHT_YELLOW);  LCD_FillRect(150,y+20*2+5,90,10);  LCD_DisplayString(0,y+20*2,"LIGHT_YELLOW");	
	LCD_SetColor(LIGHT_GREY);    LCD_FillRect(150,y+20*3+5,90,10);  LCD_DisplayString(0,y+20*3,"LIGHT_GREY");  	

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
	LCD_DrawRect(0,0,240,135); 			//���ƾ���

	LCD_SetColor(LCD_RED);    LCD_FillCircle(142,70,30);		//���Բ��
	LCD_SetColor(LCD_GREEN);  LCD_FillCircle(172,70,30); 	
	LCD_SetColor(LCD_BLUE);   LCD_FillCircle(202,70,30);  	
	
	LCD_SetColor(LCD_YELLOW);
	LCD_DrawLine(26,46,113, 84);				//��ֱ��
	LCD_DrawLine(35,42,106,101);				//��ֱ��
	LCD_DrawLine(45,40, 93,120);				//��ֱ��
	LCD_DrawLine(52,36, 69,128);				//��ֱ��
	LCD_DrawLine(62,36, 44,128);				//��ֱ��
	
	Delay_ms(1000);	
	LCD_Clear(); //������ˢ����ɫ	
	
	LCD_SetColor(LIGHT_CYAN);
	LCD_DrawCircle(120,72,30);			//����Բ��
	LCD_DrawCircle(120,72,20);   

	LCD_SetColor(LIGHT_RED);	
	LCD_DrawEllipse(120,72,90,40); 	//������Բ 
	LCD_DrawEllipse(120,72,70,40); 	//������Բ    
	LCD_SetColor(LIGHT_MAGENTA);	
	LCD_DrawEllipse(120,72,100,50); 	//������Բ
	LCD_DrawEllipse(120,72,110,60);  

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
	LCD_DrawImage( 16, 37, 60, 60, Image_Android_60x60) ;	   // ��ʾͼƬ

	LCD_SetColor( 0xff9DD3A8);
	LCD_DrawImage( 90, 37, 60, 60, Image_Toys_60x60) ;		// ��ʾͼƬ
	
	LCD_SetColor( 0xffFF8753);
	LCD_DrawImage( 164, 37, 60, 60, Image_Video_60x60) ;		// ��ʾͼƬ

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
	LCD_SetTextFont(&CH_Font24);  
	LCD_SetColor( 0xffDFF9FB);  	
	LCD_DisplayText(0,10,"Direction_V"); 	
	LCD_SetColor( 0xffF6E58D);
	LCD_DrawImage( 37,50, 60, 60, Image_Android_60x60) ;	   // ��ʾͼƬ
	LCD_SetTextFont(&CH_Font32);
	LCD_SetColor( 0xff9DD3A8);  
	LCD_DisplayText(35,130,"¹С��");
	LCD_DisplayText(35,162,"�Ƽ�");
	Delay_ms(1000);	// ��ʱ	

   LCD_SetDirection(Direction_H);		   
	LCD_SetBackColor(LCD_BLACK); 			//	���ñ���ɫ
	LCD_Clear(); 								// ����
	LCD_SetTextFont(&CH_Font24);  
	LCD_SetColor( 0xffDFF9FB);  	
	LCD_DisplayText(20,10,"Direction_H"); 	
	LCD_SetColor( 0xffF6E58D);
	LCD_DrawImage( 30,50, 60, 60, Image_Android_60x60) ;	   // ��ʾͼƬ
	LCD_SetTextFont(&CH_Font32);
	LCD_SetColor( 0xff9DD3A8);  
	LCD_DisplayText(120,45,"¹С��");
	LCD_DisplayText(120,77,"�Ƽ�");
	Delay_ms(1000);	// ��ʱ		

   LCD_SetDirection(Direction_V_Flip);		   
	LCD_SetBackColor(LCD_BLACK); 			//	���ñ���ɫ
	LCD_Clear(); 								// ����
	LCD_SetTextFont(&CH_Font16);  
	LCD_SetColor( 0xffDFF9FB);  	
	LCD_DisplayText(0,10,"Direction_V_Flip"); 	
	LCD_SetColor( 0xffF6E58D);
	LCD_DrawImage( 37,50, 60, 60, Image_Android_60x60) ;	   // ��ʾͼƬ
	LCD_SetTextFont(&CH_Font32);
	LCD_SetColor( 0xff9DD3A8);  
	LCD_DisplayText(35,130,"¹С��");
	LCD_DisplayText(35,162,"�Ƽ�");
	Delay_ms(1000);	// ��ʱ		
	
   LCD_SetDirection(Direction_H_Flip);		   
	LCD_SetBackColor(LCD_BLACK); 			//	���ñ���ɫ
	LCD_Clear(); 								// ����
	LCD_SetTextFont(&CH_Font24);  
	LCD_SetColor( 0xffDFF9FB);  	
	LCD_DisplayText(20,10,"Direction_H_Flip"); 	
	LCD_SetColor( 0xffF6E58D);
	LCD_DrawImage( 30,50, 60, 60, Image_Android_60x60) ;	   // ��ʾͼƬ
	LCD_SetTextFont(&CH_Font32);
	LCD_SetColor( 0xff9DD3A8);  
	LCD_DisplayText(120,45,"¹С��");
	LCD_DisplayText(120,77,"�Ƽ�");
	Delay_ms(1000);	// ��ʱ	
}

