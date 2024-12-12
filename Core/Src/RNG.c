#include "RNG.h"

static RNG_HandleTypeDef hrng;

void RNG_Init()
{
	__HAL_RCC_RNG_CLK_ENABLE();
	hrng.Instance = RNG;
	HAL_RNG_Init(&hrng);
	if (HAL_RNG_Init(&hrng) != HAL_OK) // error handler
	{
		while(1);
	}
}

void RNG_DeInit()
{
	hrng.Instance = RNG;
	HAL_RNG_DeInit(&hrng);
	__HAL_RCC_RNG_CLK_DISABLE();
}

uint32_t generateRandomNum()
{
	if (HAL_RNG_GetState(&hrng) != HAL_RNG_STATE_READY)
	{
		while(1);
	}
	uint32_t randomNum = 0;
	HAL_RNG_GenerateRandomNumber(&hrng, &randomNum);
	printf("%lu", randomNum);
	return (randomNum);
}
