/***
	***************************************************************************
	*	@file  	stm32f4xx_it.c
	*	@brief   �жϷ�����
   ***************************************************************************
   *  @description
	*
	*  ���ļ������STM32���е��쳣�������жϷ�����
	* 	
	***************************************************************************
***/
#include "stm32f4xx_it.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}


extern void TimingDelay_Decrement(void);	//����������������delay.c

//	������SysTick�жϷ�����
//
void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}

/******************************************************************************/
/*                				                      									*/
/*  								STM32F4xx �����жϷ����� 									*/
/*  																									*/
/******************************************************************************/


#include "sdio_sd.h"

/**
  * @brief  This function handles SDIO global interrupt request.
  * @param  None
  * @retval None
  */
void SDIO_IRQHandler(void)
{
	/* Process All SDIO Interrupt Sources */
	SD_ProcessIRQSrc();
}

/**
  * @brief  This function handles DMA2 Stream3 or DMA2 Stream6 global interrupts
  *         requests.
  * @param  None
  * @retval None
  */
void SD_SDIO_DMA_IRQHANDLER(void)
{
	/* Process DMA2 Stream3 or DMA2 Stream6 Interrupt Sources */
	SD_ProcessDMAIRQ();
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
