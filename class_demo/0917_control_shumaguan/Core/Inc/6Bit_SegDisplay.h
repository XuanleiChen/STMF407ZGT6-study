#ifndef __6BitSeg_Display
#define __6BitSeg_Display

#define GPIO_DuanXuan GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
#define GPIO_Point GPIO_PIN_3
#define Seg_bit0 GPIO_PIN_0
#define Seg_bit1 GPIO_PIN_1
#define Seg_bit2 GPIO_PIN_2
#define Seg_bit3 GPIO_PIN_3
#define Seg_bit4 GPIO_PIN_4
#define Seg_bit5 GPIO_PIN_5

#include "main.h"
#include "gpio.h"

void Seg_Control(uint16_t Wei,uint16_t Duan);
void Seg_Display(uint16_t a,uint16_t b,uint16_t c,uint16_t d,uint16_t e,uint16_t f);
void Time_Control(uint64_t Time_Value);

#endif
