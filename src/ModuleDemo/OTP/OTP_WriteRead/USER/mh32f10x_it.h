/**
  ******************************************************************************
  * @file    GPIO/IOToggle/MH32f10x_it.h 

  * @author  NONE
  * @version NONE
  * @date    NONE
  * @brief   NONE
  ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MH32F10x_IT_H
#define __MH32F10x_IT_H

/* Includes ------------------------------------------------------------------*/
#include "MH32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#endif /* __MH32F10x_IT_H */

/******************* (C) COPYRIGHT  MHSEMICONDUCTOR *****END OF FILE****/
