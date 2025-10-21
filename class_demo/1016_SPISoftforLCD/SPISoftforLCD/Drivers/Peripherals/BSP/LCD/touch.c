#include "touch.h"

/*****************************************************************************
 * @name       :void Touch_Write_Byte(u8 num)   
 * @date       :2018-08-09 
 * @function   :Write a byte data to the touch screen IC with SPI bus
 * @parameters :num:Data to be written
 * @retvalue   :None
******************************************************************************/  	 			    					   
void SPI_Write1ByteData(u8 num)    
{  
	u8 count = 0;   
	for(count = 0;count < 8; count ++)  
	{
		if(num & 0x80)
		{
			TOUCH_DIN_H();
		}
		else
		{
			TOUCH_DIN_L();
		}
		num <<= 1;    
		TOUCH_CLK_L(); 
		Delay_Xus(1);
		TOUCH_CLK_H();		//上升沿有效	        
	}		 			    
}

/*****************************************************************************
 * @name       :u16 SPI_Toggle2BytesData(u8 command)	  
 * @date       :2018-08-09 
 * @function   :Reading adc values from touch screen IC with SPI bus
 * @parameters :CMD:Read command,0xD0 for x,0x90 for y
 * @retvalue   :Read data
******************************************************************************/    
u16 SPI_Toggle2BytesData(u8 command)	  
{ 	 
	u8 count = 0;
	u16 dataWith4Bytes = 0x0000; 
	TOUCH_CLK_L();											//先拉低时钟
	TOUCH_DIN_L(); 											//拉低数据线
	TOUCH_CS_L(); 											//选中触摸屏IC
	SPI_Write1ByteData(command);				//发送命令字
	Delay_Xus(6);												//ADS7846的转换时间最长为6us
	TOUCH_CLK_L(); 	     	    
	Delay_Xus(1);    	   
	TOUCH_CLK_H();											//给1个时钟，清除BUSY
	Delay_Xus(1);    
	TOUCH_CLK_L();
	for(count = 0; count < 16; count ++)//读出16位数据但只有高12位有效
	{
		dataWith4Bytes <<= 1; 	 
		TOUCH_CLK_L();										//下降沿有效
		Delay_Xus(1);    
 		TOUCH_CLK_H();
 		if(TOUCH_DOUT_V())
		{
			dataWith4Bytes |= 0x0001;
		}
	}
	dataWith4Bytes >>= 4;   						//只有高12位有效
	TOUCH_CS_H();												//释放片选
	return dataWith4Bytes;  
}

#define TOUCH_SAMPLING_TIMES 		5 		//采样次数
#define TOUCH_LOST_TIMES 				1	  	//丢弃次数
/*****************************************************************************
 * @name       :u16 Touch_Read_XOY(u8 xy)  
 * @date       :2018-08-09 
 * @function   :Read the touch screen coordinates (x or y),
								Read the TOUCH_SAMPLING_TIMES secondary data in succession 
								and sort the data in ascending order,
								Then remove the lowest and highest number of TOUCH_LOST_TIMES 
								and take the average
 * @parameters :xy:Read command(TOUCH_X/TOUCH_Y)
 * @retvalue   :Read data
******************************************************************************/  
u16 Touch_Read_XOY(u8 xyCommand)
{
	u16 i, j;
	u16 buf[TOUCH_SAMPLING_TIMES];
	u16 sumADValue = 0;
	u16 xyADValue;
	for(i = 0; i < TOUCH_SAMPLING_TIMES; i ++)
	{
		buf[i] = SPI_Toggle2BytesData(xyCommand);
	}	    
	for(i = 0;i < TOUCH_SAMPLING_TIMES - 1; i ++)	//排序
	{
		for(j = i+1;j < TOUCH_SAMPLING_TIMES; j ++)
		{
			if(buf[i] > buf[j])												//冒泡(升序)排列
			{
				xyADValue = buf[i];
				buf[i] = buf[j];
				buf[j] = xyADValue;
			}
		}
	}	  
	sumADValue = 0;
	for(i = TOUCH_LOST_TIMES; i < TOUCH_SAMPLING_TIMES - TOUCH_LOST_TIMES; i ++)
	{
		sumADValue += buf[i];
	}
	xyADValue = sumADValue / (TOUCH_SAMPLING_TIMES - 2 * TOUCH_LOST_TIMES);
	return xyADValue;
} 

/*****************************************************************************
 * @name       :u8 Touch_Read_XY1(u16 *x,u16 *y)
 * @date       :2018-08-09 
 * @function   :Read touch screen x and y coordinates,
								The minimum value can not be less than 100
 * @parameters :x:Read x coordinate of the touch screen
								y:Read y coordinate of the touch screen
 * @retvalue   :false-fail,true-success
******************************************************************************/ 
bool Touch_Read_XY1(u16 *x, u16 *y)
{
	u16 xTemp,yTemp;			 	 		  
	xTemp = Touch_Read_XOY(TOUCH_X);
	yTemp = Touch_Read_XOY(TOUCH_Y);
	if(xTemp < 100 || yTemp < 100)
	{
		return false;//读数失败
	}
	else
	{
		*x = xTemp;
		*y = yTemp;
		return true;//读数成功
	}
}

#define TOUCH_XY_ERROR_RANGE 50 //误差范围 
/*****************************************************************************
 * @name       :u8 Touch_Read_XY2(u16 *x,u16 *y) 
 * @date       :2018-08-09 
 * @function   :Read the touch screen coordinates twice in a row, 
								and the deviation of these two times can not exceed TOUCH_XY_ERROR_RANGE, 
								satisfy the condition, then think the reading is correct, 
								otherwise the reading is wrong.
								This function can greatly improve the accuracy.
 * @parameters :x:Read x coordinate of the touch screen
								y:Read y coordinate of the touch screen
 * @retvalue   :false-fail,true-success
******************************************************************************/ 
bool Touch_Read_XY2(u16 *x, u16 *y) 
{
	u16 x1,y1,x2,y2;
 	bool flag1,flag2;
	flag1 = Touch_Read_XY1(&x1, &y1);
	flag2 = Touch_Read_XY1(&x2, &y2);
	if(flag1 == false || flag2 == false)
	{
		return false;
	}
	else
	{
		//前后两次采样在±TOUCH_XY_ERROR_RANGE内
		if(((x2 <= x1 && x1 < x2 + TOUCH_XY_ERROR_RANGE) || (x1 <= x2 && x2 < x1 + TOUCH_XY_ERROR_RANGE)) && ((y2 <= y1 && y1 < y2 + TOUCH_XY_ERROR_RANGE) || (y1 <= y2 && y2 < y1 + TOUCH_XY_ERROR_RANGE)))
		{
			*x = (x1+x2)/2;
			*y = (y1+y2)/2;
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Touch_IsPressed(void)
{
	bool isPressed = false;
	if(TOUCH_IRQ_V())
	{
		while(TOUCH_IRQ_V());
		isPressed = true;
	}
	return isPressed;
}

/*****************************************************************************
 * @name       :u8 Touch_Init(void)
 * @date       :2018-08-09 
 * @function   :Initialization touch screen
 * @parameters :None
 * @retvalue   :0-no calibration
								1-Has been calibrated
******************************************************************************/  
void Touch_Init(void)
{			    		   
	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_Initure.Pin = TOUCH_CS_PIN | TOUCH_CS_PIN | TOUCH_CLK_PIN;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_Initure);

	GPIO_Initure.Pin = TOUCH_IRQ_PIN | TOUCH_DOUT_PIN;
	GPIO_Initure.Mode = GPIO_MODE_INPUT;
	GPIO_Initure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOC, &GPIO_Initure);
}
