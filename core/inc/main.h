#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f4xx_hal.h"

void SystemClock_Config(void);
void Error_Handler(void);

// External handlers
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim1;

#endif
