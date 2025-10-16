#include "keys.h"

void Keys_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// 使能GPIOA和GPIOB时钟
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	// 配置PA0、PA1为上拉输入模式
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// 配置PB0、PB1为上拉输入模式
	// GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
	// GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	// GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

bool KeyA0_HasBeenClicked(void)
{
	bool clicked = false;	
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)  == GPIO_PIN_RESET)
	{
		HAL_Delay(25);
		while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)  == GPIO_PIN_RESET);
		HAL_Delay(25);
		clicked = true;
	}
	return clicked;
}

bool KeyA1_HasBeenClicked(void)
{
	bool clicked = false;	
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)  == GPIO_PIN_RESET)
	{
		HAL_Delay(25);
		while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)  == GPIO_PIN_RESET);
		HAL_Delay(25);
		clicked = true;
	}
	return clicked;
}

bool KeyB0_HasBeenClicked(void)
{
	bool clicked = false;	
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)  == GPIO_PIN_RESET)
	{
		HAL_Delay(25);
		while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)  == GPIO_PIN_RESET);
		HAL_Delay(25);
		clicked = true;
	}
	return clicked;
}

bool KeyB1_HasBeenClicked(void)
{
	bool clicked = false;	
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)  == GPIO_PIN_RESET)
	{
		HAL_Delay(25);
		while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)  == GPIO_PIN_RESET);
		HAL_Delay(25);
		clicked = true;
	}
	return clicked;
}
