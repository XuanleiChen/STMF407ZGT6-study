/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    i2c.h
  * @brief   This file contains all the function prototypes for
  *          the i2c.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN Private defines */
#define E2PROM_DEVICE_ADDRESS7BITS	0x50
/* USER CODE END Private defines */

void MX_I2C1_Init(void);

/* USER CODE BEGIN Prototypes */
HAL_StatusTypeDef YW_E2PROM_Read(uint8_t *buffer, uint8_t topAddress, uint16_t size);
HAL_StatusTypeDef YW_E2PROM_Write(uint8_t *buffer, uint8_t topAddress, uint16_t size);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */

