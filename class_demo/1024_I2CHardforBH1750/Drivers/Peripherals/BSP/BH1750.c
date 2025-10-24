#include "bh1750.h"
#include "i2c.h"

float BH1750_Resolution = 1;

HAL_StatusTypeDef BH1750_PowerOff(void)
{
	uint8_t command = BH1750_POWER_OFF_CMD;
	return HAL_I2C_Master_Transmit(&hi2c1, (BH1750_DEVICE_ADDRESS7BITS << 1), &command, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef BH1750_PowerOn(void)
{
	uint8_t command = BH1750_POWER_ON_CMD;
	return HAL_I2C_Master_Transmit(&hi2c1, (BH1750_DEVICE_ADDRESS7BITS << 1), &command, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef BH1750_Reset(void)
{
	uint8_t command = BH1750_RESET_CMD;
	return HAL_I2C_Master_Transmit(&hi2c1, (BH1750_DEVICE_ADDRESS7BITS << 1), &command, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef BH1750_SetModule(uint8_t mode)
{
	if ((mode == BH1750_CONTINUE_H_MODE_CMD) || (mode == BH1750_ONE_TIME_H_MODE_CMD))
	{
		BH1750_Resolution = 1;
	}
	else if ((mode == BH1750_CONTINUE_L_MODE_CMD) || (mode == BH1750_ONE_TIME_L_MODE_CMD))
	{
		BH1750_Resolution = 4;
	}
	else if ((mode == BH1750_CONTINUE_H_MODE2_CMD) || (mode == BH1750_ONE_TIME_H_MODE2_CMD))
	{
		BH1750_Resolution = 0.5;
	}
	else
	{
		BH1750_Resolution = 1;
	}
	uint8_t command = mode;
	return HAL_I2C_Master_Transmit(&hi2c1, (BH1750_DEVICE_ADDRESS7BITS << 1), &command, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef BH1750_Init(void)
{
	MX_I2C1_Init();
	if(BH1750_PowerOff() != HAL_OK)
	{
		return HAL_ERROR;
	}
	HAL_Delay(25);
	if(BH1750_PowerOn() != HAL_OK)
	{
		return HAL_ERROR;
	}
	HAL_Delay(25);
	if(BH1750_Reset() != HAL_OK)
	{
		return HAL_ERROR;
	}
	HAL_Delay(25);
	if(BH1750_SetModule(BH1750_CONTINUE_H_MODE_CMD) != HAL_OK)
	{
		return HAL_ERROR;
	}
	HAL_Delay(220);
	return HAL_OK;
}

HAL_StatusTypeDef BH1750_GetData(float *lightIntensity)
{	
	uint8_t buffer[2];
	if (HAL_I2C_Master_Receive(&hi2c1, (BH1750_DEVICE_ADDRESS7BITS << 1) | 0x01, buffer, 2, HAL_MAX_DELAY) != HAL_OK)
	{
		return HAL_ERROR;
	}
	uint8_t byteH = buffer[0];
	uint8_t byteL = buffer[1];
	uint16_t raw = ((uint16_t)byteH << 8) | byteL;
	*lightIntensity = (double)raw * BH1750_Resolution;
	return HAL_OK;
}
