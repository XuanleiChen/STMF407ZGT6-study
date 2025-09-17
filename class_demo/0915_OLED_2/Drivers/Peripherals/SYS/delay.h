#ifndef __DELAY_H
	#define __DELAY_H

	#include "main.h"

	// 秒级延时（X：延时秒数，范围1~65535）
	void delay_Xs(uint16_t X);

	// 毫秒级延时（X：延时毫秒数，范围1~65535）
	void delay_Xms(uint16_t X);

	// 微秒级延时（X：延时微秒数，范围1~65535）
	void delay_Xus(uint16_t X);

#endif
