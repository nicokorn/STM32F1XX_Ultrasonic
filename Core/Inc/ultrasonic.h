/**
  ******************************************************************************
  * @file           : ultrasonic.h
  * @brief          : ultrasonic c header file
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void ultrasonic_init( void );
uint16_t getDistance( void );

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __ULTRASONIC_H*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
