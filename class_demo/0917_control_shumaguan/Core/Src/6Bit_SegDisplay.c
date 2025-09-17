#include "6Bit_SegDisplay.h"

uint8_t zhenzhi[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

void Seg_Control(uint16_t Wei,uint16_t Duan)
{
	HAL_GPIO_WritePin(GPIOC,GPIO_DuanXuan,GPIO_PIN_SET);
	
	uint16_t temp;
	temp=GPIOC->ODR;
	temp&=0x003f;
	temp|=zhenzhi[Duan]<<6;
	GPIOC->ODR=temp;
	
	HAL_GPIO_WritePin(GPIOG,GPIO_Point,GPIO_PIN_RESET);
	
	switch(Wei){
		case 0:
			HAL_GPIO_WritePin(GPIOC,Seg_bit0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOG,GPIO_Point,GPIO_PIN_SET);
		break;
		
		case 1:
			HAL_GPIO_WritePin(GPIOC,Seg_bit1,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOG,GPIO_Point,GPIO_PIN_SET);
		break;
		
		case 2:
			HAL_GPIO_WritePin(GPIOC,Seg_bit2,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOG,GPIO_Point,GPIO_PIN_SET);
		break;
		
		case 3:
			HAL_GPIO_WritePin(GPIOC,Seg_bit3,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOG,GPIO_Point,GPIO_PIN_SET);
		break;
		
		case 4:
			HAL_GPIO_WritePin(GPIOC,Seg_bit4,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOG,GPIO_Point,GPIO_PIN_RESET);
		break;
		
		case 5:
			HAL_GPIO_WritePin(GPIOC,Seg_bit5,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOG,GPIO_Point,GPIO_PIN_SET);
		break;
	}
}

void Seg_Display(uint16_t a,uint16_t b,uint16_t c,uint16_t d,uint16_t e,uint16_t f)
{
		Seg_Control(0,a);
		HAL_Delay(2);
		Seg_Control(1,b);
		HAL_Delay(2);
		Seg_Control(2,c);
		HAL_Delay(2);
		Seg_Control(3,d);
		HAL_Delay(2);
		Seg_Control(4,e);
		HAL_Delay(2);
		Seg_Control(5,f);
		HAL_Delay(2);
}

void Time_Control(uint64_t Time_Value)
{

    uint8_t hour = (Time_Value / 10000) % 100; 
    uint8_t minute = (Time_Value / 100) % 100; 
    uint8_t second = Time_Value % 100;         

    
    if (hour >= 24) hour = 0;
    if (minute >= 60) minute = 0;
    if (second >= 60) second = 0;

    
    while (1)
    {
    
        uint8_t H0 = hour / 10;
        uint8_t H1 = hour % 10;
        uint8_t M0 = minute / 10;
        uint8_t M1 = minute % 10;
        uint8_t S0 = second / 10;
        uint8_t S1 = second % 10;

    
        for (int i = 0; i < 83; i++){
            Seg_Display(H0, H1, M0, M1, S0, S1);
        }
    
        HAL_Delay(2);

        second++;
    
        if (second >= 60){
            second = 0;
            minute++;
            if (minute >= 60){
                minute = 0;
                hour++;
                if (hour >= 24){
                    hour = 0;
                }
            }
        }
    }
}