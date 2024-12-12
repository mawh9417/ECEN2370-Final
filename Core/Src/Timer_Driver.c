#include "Timer_Driver.h"

static TIM_HandleTypeDef hrng;

void TIM2_Init()
{
	hrng.Instance = TIM2;
	hrng.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	hrng.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	hrng.Init.CounterMode = TIM_COUNTERMODE_UP;
	hrng.Init.Period = 999;
	hrng.Init.Prescaler = 15999;
	hrng.Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(&hrng);
}

void TIM2_Start()
{
	HAL_TIM_Base_Start_IT(&hrng);
}

void TIM2_Stop()
{
	HAL_TIM_Base_Stop_IT(&hrng);
}
