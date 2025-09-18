#include "ic74hc138.h"
void IC74HC138_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12,GPIO_PIN_RESET);

  /*Configure GPIO pins : PG3 PG4 PG7 PG10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}
void  Light(uint16_t Data)
{
		if (Data<8)
		{
			uint8_t temp=GPIOC->ODR;
			temp &=0xE3FF;
			temp |= (uint16_t) Data<<10;
			
		}
	
}
