#include "Timer_Driver.h"

TIM_HandleTypeDef htim;

void TIM6_Init()
{
	__HAL_RCC_TIM6_CLK_ENABLE();
	htim.Instance = TIM6;
	htim.Init.Prescaler = 265;
	htim.Init.Period = 59999;
	htim.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	HAL_TIM_Base_Init(&htim);
}

void TIM6_Start()
{
	HAL_TIM_Base_Start_IT(&htim);
}

void TIM6_Stop()
{
	HAL_TIM_Base_Stop_IT(&htim);
}


