#ifndef __DELAY_H
	#define __DELAY_H

	#include "main.h"
	
	void Delay_Init(void);

	// 秒级延时（s：延时秒数）
	void Delay_Xs(uint32_t s);

	// 毫秒级延时（ms：延时毫秒数）
	void Delay_Xms(uint32_t ms);

	// 微秒级延时（us：延时微秒数）
	void Delay_Xus(uint32_t us);

#endif
