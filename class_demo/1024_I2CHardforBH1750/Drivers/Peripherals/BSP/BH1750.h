#ifndef __BH1750_H
	#define __BH1750_H

	#include "main.h"
	#define BH1750_DEVICE_ADDRESS7BITS	0x23
	
	//根据BH1750的官方手册，定义如下常用指令集
	
	//初始化有关的指令
	#define BH1750_POWER_OFF_CMD				0x00
	#define BH1750_POWER_ON_CMD					0x01
	#define BH1750_RESET_CMD						0x07
	
	//工作模式有关的指令
	#define BH1750_CONTINUE_H_MODE_CMD	0x10	//连续高分辨率模式
	#define BH1750_CONTINUE_H_MODE2_CMD	0x11	//连续高分辨率模式2
	#define BH1750_CONTINUE_L_MODE_CMD	0x13	//连续低分辨率模式
	
	#define BH1750_ONE_TIME_H_MODE_CMD	0x20	//一次高分辨率模式
	#define BH1750_ONE_TIME_H_MODE2_CMD	0x21	//一次高分辨率模式2	
	#define BH1750_ONE_TIME_L_MODE_CMD	0x23	//一次低分辨率模式

	HAL_StatusTypeDef BH1750_Init(void);
	HAL_StatusTypeDef BH1750_GetData(float *lightIntensity);
#endif
