#ifndef __TOUCH_H
	#define __TOUCH_H
	#include "main.h"


	#define TOUCH_X 								0xD0
	#define TOUCH_Y 								0x90
	typedef enum
	{
		Portrait_Mode = 0U,						//适合左右为X坐标上下为Y坐标的TP
		Landscape_Mode = 1U						//适合左右为Y坐标上下为X坐标的TP
	} Screen_Mode;
	
	typedef enum
	{
		Screen_Coordinate = 0U,				//屏幕屏幕
		Physical_Coordinate = 1U			//物理坐标
	} Coordinate_Type;
	 
	//触摸屏控制器
	typedef struct
	{
		u8 	ScreenMode;								//屏幕方向
		u8 	CoordinateType;						//坐标类型
		u16 Xo;												//原始横坐标(第一次按下时的横坐标)
		u16 Yo;												//原始众坐标(第一次按下时的众坐标)
		u16 Xn; 											//当前横坐标(此次扫描时触屏的横坐标)
		u16 Yn;												//当前众坐标(此次扫描时触屏的众坐标)
		u8  PressStatus;							//笔的状态
																	//b7 b6 0 0 0 0 0 0
																	//b7:1触屏已被按下、0触屏未被按下或松开
																	//b6:1有按键被按下、0没有按键被按下或松开
	}TouchPad_Attribute;

	extern TouchPad_Attribute 	myTouchPad;	 	//触屏控制器在touch.c里面定义

	// 触摸屏GPIO定义
	#define TOUCH_CLK_PIN   GPIO_PIN_4						//触摸屏SPI时钟信号
	#define TOUCH_CS_PIN    GPIO_PIN_3						//触摸屏SPI片选控制信号
	#define TOUCH_DIN_PIN   GPIO_PIN_2						//触摸屏SPI写信号
	#define TOUCH_DOUT_PIN  GPIO_PIN_1						//触摸屏SPI读信号
	#define TOUCH_IRQ_PIN   GPIO_PIN_0						//触摸屏SPI触摸中断信号
	
	//-----------------LCD端口定义----------------	
	#define TOUCH_CLK_L() 	HAL_GPIO_WritePin(GPIOC, TOUCH_CLK_PIN, GPIO_PIN_RESET)
	#define TOUCH_CLK_H() 	HAL_GPIO_WritePin(GPIOC, TOUCH_CLK_PIN, GPIO_PIN_SET)
		 
	#define TOUCH_CS_L()   	HAL_GPIO_WritePin(GPIOC, TOUCH_CS_PIN, GPIO_PIN_RESET)
	#define TOUCH_CS_H()   	HAL_GPIO_WritePin(GPIOC, TOUCH_CS_PIN, GPIO_PIN_SET)
	
	#define TOUCH_DIN_L() 	HAL_GPIO_WritePin(GPIOC, TOUCH_DIN_PIN, GPIO_PIN_RESET)
	#define TOUCH_DIN_H() 	HAL_GPIO_WritePin(GPIOC, TOUCH_DIN_PIN, GPIO_PIN_SET)
	
	#define TOUCH_DOUT_V() 	HAL_GPIO_ReadPin(GPIOC, TOUCH_DOUT_PIN)
	
	#define TOUCH_IRQ_V() 	HAL_GPIO_ReadPin(GPIOC, TOUCH_IRQ_PIN)

   
	void Touch_Write_Byte(u8 num);								//向控制芯片写入一个数据
	u16 SPI_Toggle2BytesData(u8 command);						//模拟SPI时序些指定寄存器并交换出4个字节（AD转换值）
	u16 Touch_Read_XOY(u8 xy);									//带滤波的坐标读取(X/Y)
	bool Touch_Read_XY1(u16 *x, u16 *y);						//双方向读取(X+Y)
	bool Touch_Read_XY2(u16 *x, u16 *y);						//带加强滤波的双方向坐标读取
	bool Touch_IsPressed(void);									//扫描是否被按下
	void Touch_Init(void);										//初始化																	 
#endif
