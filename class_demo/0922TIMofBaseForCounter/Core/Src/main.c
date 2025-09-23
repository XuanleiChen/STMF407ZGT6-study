/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/*引脚配置*/
#define OLED_W_SCL(x)		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (GPIO_PinState)(x))
#define OLED_W_SDA(x)		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, (GPIO_PinState)(x))

/*引脚初始化*/
void OLED_I2C_Init(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitTypeDef YuWei_GPIO_InitStructure;
 	YuWei_GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
	YuWei_GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	YuWei_GPIO_InitStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7;
 	HAL_GPIO_Init(GPIOB, &YuWei_GPIO_InitStructure);
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

/**
  * @brief  I2C开始
  * @param  无
  * @retval 无
  */
void OLED_I2C_Start(void)
{
	OLED_W_SDA(1);
	OLED_W_SCL(1);
	OLED_W_SDA(0);
	OLED_W_SCL(0);
}

/**
  * @brief  I2C停止
  * @param  无
  * @retval 无
  */
void OLED_I2C_Stop(void)
{
	OLED_W_SDA(0);
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

/**
  * @brief  I2C发送一个字节
  * @param  Byte 要发送的一个字节
  * @retval 无
  */
void OLED_I2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		OLED_W_SDA(Byte & (0x80 >> i));
		OLED_W_SCL(1);
		OLED_W_SCL(0);
	}
	OLED_W_SCL(1);	//额外的一个时钟，不处理应答信号
	OLED_W_SCL(0);
}

/**
  * @brief  OLED写命令
  * @param  Command 要写入的命令
  * @retval 无
  */
void OLED_WriteCommand(uint8_t Command)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//从机地址
	OLED_I2C_SendByte(0x00);		//写命令
	OLED_I2C_SendByte(Command);
	OLED_I2C_Stop();
}

/**
  * @brief  OLED写数据
  * @param  Data 要写入的数据
  * @retval 无
  */
void OLED_WriteData(uint8_t Data)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//从机地址
	OLED_I2C_SendByte(0x40);		//写数据
	OLED_I2C_SendByte(Data);
	OLED_I2C_Stop();
}

/**
  * @brief  OLED设置光标位置
  * @param  Y 以左上角为原点，向下方向的坐标，范围：0~7
  * @param  X 以左上角为原点，向右方向的坐标，范围：0~127
  * @retval 无
  */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
	OLED_WriteCommand(0xB0 | Y);					//设置Y位置
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//设置X位置低4位
	OLED_WriteCommand(0x00 | (X & 0x0F));			//设置X位置高4位
}

/**
  * @brief  OLED清屏
  * @param  无
  * @retval 无
  */
void OLED_Clear(void)
{
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		OLED_SetCursor(j, 0);
		for(i = 0; i < 128; i++)
		{
			OLED_WriteData(0x00);
		}
	}
}

/**
  * @brief  OLED显示一个字符
  * @param  Row 行位置，范围：1~4
  * @param  Column 列位置，范围：1~16
  * @param  Character 要显示的一个字符，范围：ASCII可见字符
  * @retval 无
  */
void OLED_ShowCharacter(uint8_t Row, uint8_t Column, char Character)
{
	uint8_t i;
	OLED_SetCursor((Row - 1) * 2, (Column - 1) * 8);			//设置光标位置在上半部分
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Character - ' '][i]);			//显示上半部分内容
	}
	OLED_SetCursor((Row - 1) * 2 + 1, (Column - 1) * 8);		//设置光标位置在下半部分
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Character - ' '][i + 8]);		//显示下半部分内容
	}
}

/**
  * @brief  OLED显示字符串
  * @param  Row 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  String 要显示的字符串，范围：ASCII可见字符
  * @retval 无
  */
void OLED_ShowString(uint8_t Row, uint8_t Column, char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)
	{
		OLED_ShowCharacter(Row, Column + i, String[i]);
	}
}

typedef struct
{
	char Index[3];
	char Mask[32];
}GB16;

//宋体
//16*16大小
//逐行式，顺向（高位在前）
const GB16 OLED_F16x16[] =
{
	"余",0x80,0x80,0x40,0x20,0x50,0x48,0x44,0xC3,0x44,0x48,0x50,0x20,0x40,0x80,0x80,0x00,0x00,0x40,0x22,0x1A,0x02,0x42,0x82,0x7F,0x02,0x02,0x02,0x0A,0x12,0x60,0x00,0x00,
	"伟",0x00,0x80,0x60,0xF8,0x07,0x08,0x48,0x48,0x48,0xFF,0x48,0x48,0x48,0x48,0x08,0x00,0x01,0x00,0x00,0xFF,0x00,0x02,0x02,0x02,0x02,0xFF,0x02,0x02,0x12,0x22,0x1E,0x00,
	"●",0x00,0xE0,0xF8,0xFC,0xFC,0xFE,0xFE,0xFE,0xFE,0xFE,0xFC,0xFC,0xF8,0xE0,0x00,0x00,0x00,0x03,0x0F,0x1F,0x1F,0x3F,0x3F,0x3F,0x3F,0x3F,0x1F,0x1F,0x0F,0x03,0x00,0x00,
	"○",0x00,0xE0,0xF8,0x1C,0x04,0x06,0x02,0x02,0x02,0x06,0x04,0x1C,0xF8,0xE0,0x00,0x00,0x00,0x03,0x0F,0x1C,0x10,0x30,0x20,0x20,0x20,0x30,0x10,0x1C,0x0F,0x03,0x00,0x00,
	"·",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	"→",0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x90,0xA0,0xE0,0xC0,0xC0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x02,0x03,0x01,0x01,0x00,0x00,0x00,
	"省",0x00,0x10,0x88,0x86,0xC0,0xC0,0xA0,0xAF,0x90,0x90,0x88,0x82,0x84,0x08,0x00,0x00,0x01,0x01,0x00,0xFF,0x4A,0x4A,0x4A,0x4A,0x4A,0x4A,0x4A,0x4A,0xFF,0x00,0x00,0x00,
	"市",0x00,0x08,0x88,0x88,0x88,0x88,0x89,0xFA,0x88,0x88,0x88,0x88,0x88,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x10,0x20,0x1F,0x00,0x00,0x00,
	"·",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	"°",0x00,0x00,0x0C,0x12,0x12,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	"…",0x00,0xC0,0xC0,0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	"：",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	"℃",0x06,0x09,0x09,0xE6,0xF8,0x0C,0x04,0x02,0x02,0x02,0x02,0x02,0x04,0x1E,0x00,0x00,0x00,0x00,0x00,0x07,0x1F,0x30,0x20,0x40,0x40,0x40,0x40,0x40,0x20,0x10,0x00,0x00,
	"％",0x00,0x00,0x7C,0x82,0x82,0x7C,0x00,0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x00,0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00,0x3E,0x41,0x41,0x3E,0x00,0x00,0x00,0x00,
	"㎡",0x00,0x10,0xE0,0x10,0x10,0xE0,0x10,0x10,0xE0,0x00,0x44,0x62,0x52,0x4C,0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x0F,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

/**
  * @brief  OLED显示汉字
  * @param  Row 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  CH 要显示的数字，范围：前文OLED_F16x16内部定义的汉字
  * @retval 无
  */
void OLED_ShowChinese(uint8_t Row, uint8_t Column, char *CH)
{
	uint8_t i,j,k,n = 0;
	char *p = CH;
	while (*p++ != '\0')
	{
		n ++;
	}
	for(k = 0; k < n; k +=3)
	{
		for(i = 0; i < sizeof(OLED_F16x16)/sizeof(GB16); i ++)
		{
			if((OLED_F16x16[i].Index[0] == CH[k]) && (OLED_F16x16[i].Index[1] == CH[k+1]) && (OLED_F16x16[i].Index[2] == CH[k+2]))
			{
				OLED_SetCursor((Row - 1) * 2, (Column - 1) * 8 + 8 * 2*k/3);			//设置光标位置在上半部分
				for (j = 0; j < 16; j ++)
				{
					OLED_WriteData(OLED_F16x16[i].Mask[j]);													//显示上半部分内容
				}
				OLED_SetCursor((Row - 1) * 2 + 1, (Column - 1) * 8 + 8 * 2*k/3);	//设置光标位置在下半部分
				for (j = 0; j < 16; j ++)
				{
					OLED_WriteData(OLED_F16x16[i].Mask[j + 16]);										//显示下半部分内容
				}
			}
		}
	}
}

/**
  * @brief  OLED次方函数
  * @retval 返回值等于X的Y次方
  */
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)
	{
		Result *= X;
	}
	return Result;
}

/**
  * @brief  OLED显示数字（十进制，正数）
  * @param  Row 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Integer 要显示的数字，范围：0~4294967295
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval 无
  */
void OLED_ShowInteger(uint8_t Row, uint8_t Column, uint32_t Integer, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)
	{
		OLED_ShowCharacter(Row, Column + i, Integer / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
  * @brief  OLED显示数字（十进制，带符号数）
  * @param  Row 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Integer 要显示的数字，范围：-2147483648~2147483647
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval 无
  */
void OLED_ShowSignedInteger(uint8_t Row, uint8_t Column, int32_t Integer, uint8_t Length)
{
	uint8_t i;
	uint32_t Integer1;
	if (Integer >= 0)
	{
		OLED_ShowCharacter(Row, Column, '+');
		Integer1 = Integer;
	}
	else
	{
		OLED_ShowCharacter(Row, Column, '-');
		Integer1 = -Integer;
	}
	for (i = 0; i < Length; i++)
	{
		OLED_ShowCharacter(Row, Column + i + 1, Integer1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
  * @brief  OLED显示数字（十六进制，正数）
  * @param  Row 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Integer 要显示的数字，范围：0~0xFFFFFFFF
  * @param  Length 要显示数字的长度，范围：1~8
  * @retval 无
  */
void OLED_ShowHexInteger(uint8_t Row, uint8_t Column, uint32_t Integer, uint8_t Length)
{
	uint8_t i,SingleInteger;
	OLED_ShowCharacter(Row, Column + 0, '0');
	OLED_ShowCharacter(Row, Column + 1, 'x');
	for (i = 0; i < Length; i++)
	{
		SingleInteger = Integer / OLED_Pow(16, Length - i - 1) % 16;
		if (SingleInteger < 10)
		{
			OLED_ShowCharacter(Row, Column + i + 2, SingleInteger + '0');
		}
		else
		{
			OLED_ShowCharacter(Row, Column + i + 2, SingleInteger - 10 + 'A');
		}
	}
}

/**
  * @brief  OLED显示数字（二进制，正数）
  * @param  Row 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Integer 要显示的数字，范围：0~1111 1111 1111 1111
  * @param  Length 要显示数字的长度，范围：1~16
  * @retval 无
  */
void OLED_ShowBinInteger(uint8_t Row, uint8_t Column, uint32_t Integer, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)
	{
		OLED_ShowCharacter(Row, Column + i, Integer / OLED_Pow(2, Length - i - 1) % 2 + '0');
	}
}

/**
  * @brief  OLED显示无符号浮点数
  * @param  Row 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~+999.99
  * @param  LengthOfIntegralPart 要显示整数部分的长度，范围：3~1
  * @param  LengthOfDecimalPart 要显示小数部分的长度，范围：0~2
  * @retval 无
  */
void OLED_ShowUnsignedFloat(uint8_t Row, uint8_t Column, float Number, uint8_t LengthOfIntegralPart, uint8_t LengthOfDecimalPart)
{
	uint32_t i2,i1,i0,f1,f2;
	i2 = (uint32_t)Number % 1000 / 100;						//求百位
	i1 = (uint32_t)Number % 100 / 10;						//求十位
	i0 = (uint32_t)Number % 10 / 1;   						//求个位
	f1 = ((Number-(uint32_t)Number))*10;					//求小数点后一位
	f2 = (uint32_t)((Number-(uint32_t)Number)*100)%10;		//求小数点后两位

	if(LengthOfIntegralPart == 1)
	{
		if(LengthOfDecimalPart == 0)
		{
			OLED_ShowInteger(Row, Column + 0, i0 ,1);
		}
		else if(LengthOfDecimalPart == 1)
		{
			OLED_ShowInteger(Row, Column + 0, i0 ,1);
			OLED_ShowCharacter(Row, Column + 1, '.');
			OLED_ShowInteger(Row, Column + 2, f1 ,1);
		}
		else
		{
			OLED_ShowInteger(Row, Column + 0, i0 ,1);
			OLED_ShowCharacter(Row, Column + 1, '.');
			OLED_ShowInteger(Row, Column + 2, f1 ,1);
			OLED_ShowInteger(Row, Column + 3, f2 ,1);
		}
	}
	else if(LengthOfIntegralPart == 2)
	{
		if(LengthOfDecimalPart == 0)
		{
			OLED_ShowInteger(Row, Column + 0, i1 ,1);
			OLED_ShowInteger(Row, Column + 1, i0 ,1);
		}
		else if(LengthOfDecimalPart == 1)
		{
			OLED_ShowInteger(Row, Column + 0, i1 ,1);
			OLED_ShowInteger(Row, Column + 1, i0 ,1);
			OLED_ShowCharacter(Row, Column + 2, '.');
			OLED_ShowInteger(Row, Column + 3, f1 ,1);
		}
		else
		{
			OLED_ShowInteger(Row, Column + 0, i1 ,1);
			OLED_ShowInteger(Row, Column + 1, i0 ,1);
			OLED_ShowCharacter(Row, Column + 2, '.');
			OLED_ShowInteger(Row, Column + 3, f1 ,1);
			OLED_ShowInteger(Row, Column + 4, f2 ,1);
		}
	}
	else
	{
		if(LengthOfDecimalPart == 0)
		{
			OLED_ShowInteger(Row, Column + 0, i2 ,1);
			OLED_ShowInteger(Row, Column + 1, i1 ,1);
			OLED_ShowInteger(Row, Column + 2, i0 ,1);
		}
		else if(LengthOfDecimalPart == 1)
		{
			OLED_ShowInteger(Row, Column + 0, i2 ,1);
			OLED_ShowInteger(Row, Column + 1, i1 ,1);
			OLED_ShowInteger(Row, Column + 2, i0 ,1);
			OLED_ShowCharacter(Row, Column + 3, '.');
			OLED_ShowInteger(Row, Column + 4, f1 ,1);
		}
		else
		{
			OLED_ShowInteger(Row, Column + 0, i2 ,1);
			OLED_ShowInteger(Row, Column + 1, i1 ,1);
			OLED_ShowInteger(Row, Column + 2, i0 ,1);
			OLED_ShowCharacter(Row, Column + 3, '.');
			OLED_ShowInteger(Row, Column + 4, f1 ,1);
			OLED_ShowInteger(Row, Column + 5, f2 ,1);
		}
	}
}

/**
  * @brief  OLED显示浮点数
  * @param  Row 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：-999.99~+999.99
  * @param  LengthOfIntegralPart 要显示整数部分的长度，范围：3~1
  * @param  LengthOfDecimalPart 要显示小数部分的长度，范围：0~2
  * @retval 无
  */
void OLED_ShowSignedFloat(uint8_t Row, uint8_t Column, float Number, uint8_t LengthOfIntegralPart, uint8_t LengthOfDecimalPart)
{
	float AbsoluteValue = Number >= 0 ? Number : -Number;
	if(Number > 0)
	{
		OLED_ShowCharacter(Row, Column, '+');
	}
	else if(Number < 0)
	{
		OLED_ShowCharacter(Row, Column, '-');
	}
	else
	{
		OLED_ShowCharacter(Row, Column, ' ');
	}
	OLED_ShowUnsignedFloat(Row, Column+1, AbsoluteValue, LengthOfIntegralPart, LengthOfDecimalPart);
}

/**
  * @brief  OLED初始化
  * @param  无
  * @retval 无
  */
void OLED_Init(void)
{
	HAL_Delay(250);

	OLED_I2C_Init();					//端口初始化

	OLED_WriteCommand(0xAE);	//关闭显示

	OLED_WriteCommand(0xD5);	//设置显示时钟分频比/振荡器频率
	OLED_WriteCommand(0x80);

	OLED_WriteCommand(0xA8);	//设置多路复用率
	OLED_WriteCommand(0x3F);

	OLED_WriteCommand(0xD3);	//设置显示偏移
	OLED_WriteCommand(0x00);

	OLED_WriteCommand(0x40);	//设置显示开始行

	OLED_WriteCommand(0xA1);	//设置左右方向，0xA1正常 0xA0左右反置

	OLED_WriteCommand(0xC8);	//设置上下方向，0xC8正常 0xC0上下反置

	OLED_WriteCommand(0xDA);	//设置COM引脚硬件配置
	OLED_WriteCommand(0x12);

	OLED_WriteCommand(0x81);	//设置对比度控制
	OLED_WriteCommand(0xCF);

	OLED_WriteCommand(0xD9);	//设置预充电周期
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//设置VCOMH取消选择级别
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//设置整个显示打开/关闭

	OLED_WriteCommand(0xA6);	//设置正常/倒转显示

	OLED_WriteCommand(0x8D);	//设置充电泵
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//开启显示

	OLED_Clear();							//OLED清屏
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
   OLED_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint8_t T=0;

  while (1)
  {
    /* USER CODE END WHILE */
    OLED_ShowInteger(1,1,T,3);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
