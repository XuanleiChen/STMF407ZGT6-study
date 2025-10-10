#ifndef __SR03_H
#define __SR03_H

#include "main.h"
#include "tim.h"
#include "delay.h"

#define TRIG_H  HAL_GPIO_WritePin(Trig_GPIO_Port,Trig_Pin,GPIO_PIN_SET)
#define TRIG_L  HAL_GPIO_WritePin(Trig_GPIO_Port,Trig_Pin,GPIO_PIN_RESET)
 
uint16_t SR04_GetData(void);
 
#endif
