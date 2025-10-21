#ifndef __DISPLAY_H
	#define __DISPLAY_H
	#include "main.h"

	#define SHORT_SIDE 					240
	#define LONG_SIDE 					320
	
	typedef enum
	{
		Portrait_Upright 				= 0,		//竖屏正向
		Landscape_Rotated_Right = 3,		//横屏朝右
		Portrait_Upside_Down 		= 6,		//竖屏反向
		Landscape_Rotated_Left 	= 9			//横屏朝左
	} DISPLAY_DIRECTION;							//显示方向
	
	extern u8 Display_Direction;
	extern u16 Display_Width;
	extern u16 Display_Height;

	// 显示屏GPIO定义
	#define DISPLAY_SDO_PIN		GPIO_PIN_5				//SDO（MISO）
	#define DISPLAY_SCK_PIN		GPIO_PIN_7				//SCK
	#define DISPLAY_SDI_PIN		GPIO_PIN_8				//SDI（MOSI）
	#define DISPLAY_DC_PIN		GPIO_PIN_9				//DC
	#define DISPLAY_RESET_PIN	GPIO_PIN_10				//RESET
	#define DISPLAY_CS_PIN		GPIO_PIN_11				//CS

	//-----------------LCD端口定义---------------- 
	#define DISPLAY_SDO_V() 	HAL_GPIO_ReadPin(GPIOC, DISPLAY_SDO_PIN)

	#define DISPLAY_LED_L() 	HAL_GPIO_WritePin(GPIOC, DISPLAY_LED_PIN, GPIO_PIN_RESET)
	#define DISPLAY_LED_H() 	HAL_GPIO_WritePin(GPIOC, DISPLAY_LED_PIN, GPIO_PIN_SET)

	#define DISPLAY_SCK_L() 	HAL_GPIO_WritePin(GPIOC, DISPLAY_SCK_PIN, GPIO_PIN_RESET)
	#define DISPLAY_SCK_H() 	HAL_GPIO_WritePin(GPIOC, DISPLAY_SCK_PIN, GPIO_PIN_SET)

	#define DISPLAY_SDI_L() 	HAL_GPIO_WritePin(GPIOC, DISPLAY_SDI_PIN, GPIO_PIN_RESET)
	#define DISPLAY_SDI_H() 	HAL_GPIO_WritePin(GPIOC, DISPLAY_SDI_PIN, GPIO_PIN_SET)

	#define DISPLAY_DC_L()   	HAL_GPIO_WritePin(GPIOC, DISPLAY_DC_PIN, GPIO_PIN_RESET)
	#define DISPLAY_DC_H()   	HAL_GPIO_WritePin(GPIOC, DISPLAY_DC_PIN, GPIO_PIN_SET)

	#define DISPLAY_RESET_L() HAL_GPIO_WritePin(GPIOC, DISPLAY_RESET_PIN, GPIO_PIN_RESET)
	#define DISPLAY_RESET_H() HAL_GPIO_WritePin(GPIOC, DISPLAY_RESET_PIN, GPIO_PIN_SET)
		 
	#define DISPLAY_CS_L()   	HAL_GPIO_WritePin(GPIOC, DISPLAY_CS_PIN, GPIO_PIN_RESET)
	#define DISPLAY_CS_H()   	HAL_GPIO_WritePin(GPIOC, DISPLAY_CS_PIN, GPIO_PIN_SET)

	//void SPI_Write1Byte(u8 byte);																														//模拟SPI时序写入一个字节
	//void Display_Write1ByteData(u8 data);																										//写入一个字节数据
	//void Display_Write2BytesData(u16 data);																									//写入两个字节数据
	//void Display_WriteCommand(u8 data);																											//写入一个指令(8bits)
	//void Display_SetAddress(u16 x1, u16 y1, u16 x2, u16 y2);																//设置坐标函数

	void Display_Init(DISPLAY_DIRECTION displayDirection);																		//初始化
	void Display_SeDirection(DISPLAY_DIRECTION displayDirection);															//设置屏显方向
	u16 Display_GetID(void);																																	//获取驱动芯片编号
	void Display_Fill(u16 xsta, u16 ysta, u16 xend, u16 yend, u16 color);											//指定区域填充颜色
	void Display_DrawPoint(u16 x, u16 y, u16 color);																					//在指定位置画一个点
	void Display_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);													//在指定位置画一条线
	void Display_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);										//在指定位置画一个矩形
	void Display_DrawCircle(u16 x0, u16 y0, u8 r, u16 color);																	//在指定位置画一个圆
	void Display_ShowChinese(u16 x, u16 y, char *s, u16 fc, u16 bc, u8 sizey, u8 mode);				//显示汉字串
	void Display_ShowChinese12x12(u16 x, u16 y, char *s, u16 fc, u16 bc, u8 sizey, u8 mode);	//显示单个12x12汉字
	void Display_ShowChinese16x16(u16 x, u16 y, char *s, u16 fc, u16 bc, u8 sizey, u8 mode);	//显示单个16x16汉字
	void Display_ShowChinese24x24(u16 x, u16 y, char *s, u16 fc, u16 bc, u8 sizey, u8 mode);	//显示单个24x24汉字
	void Display_ShowChinese32x32(u16 x, u16 y, char *s, u16 fc, u16 bc, u8 sizey, u8 mode);	//显示单个32x32汉字
	void Display_ShowCharacter(u16 x, u16 y, u8 num, u16 fc, u16 bc, u8 sizey, u8 mode);			//显示一个字符
	void Display_ShowString(u16 x, u16 y, const char *p, u16 fc, u16 bc, u8 sizey, u8 mode);	//显示字符串
	void Display_ShowInteger(u16 x, u16 y, u16 num, u8 len, u16 fc, u16 bc, u8 sizey);				//显示整数变量
	void Display_ShowFloat(u16 x, u16 y, float num, u8 len, u16 fc, u16 bc, u8 sizey);				//显示两位小数变量
	void Display_ShowPicture(u16 x, u16 y, u16 height, u16 width, const u8 pic[]);						//显示图片

	//画笔颜色
	#define WHITE         	 	0xFFFF
	#define BLACK         	 	0x0000
	#define BLUE           	 	0x001F
	#define BRED            	0xF81F
	#define GRED 			 				0xFFE0
	#define GBLUE							0x07FF
	#define RED           	 	0xF800
	#define MAGENTA       	 	0xF81F
	#define GREEN         	 	0x07E0
	#define CYAN          	 	0x7FFF
	#define YELLOW        	 	0xFFE0
	#define BROWN 			    	0xBC40 //棕色
	#define BRRED 			    	0xFC07 //棕红色
	#define GRAY  			    	0x8430 //灰色
	#define DARKBLUE      	 	0x01CF //深蓝色
	#define LIGHTBLUE      	 	0x7D7C //浅蓝色  
	#define GRAYBLUE       	 	0x5458 //灰蓝色
	#define LIGHTGREEN     	 	0x841F //浅绿色
	#define LGRAY 						0xC618 //浅灰色(窗体背景色)
	#define LGRAYBLUE        	0xA651 //浅灰蓝色(中间层颜色)
	#define LBBLUE           	0x2B12 //浅棕蓝色(选择条目的反色)

	
#endif
