#ifndef RNG_H_
#define RNG_H_

#include <stdio.h>
#include "stm32f4xx_hal.h"

void RNG_Init();
void RNG_DeInit();
uint32_t generateRandomNum();

#endif
