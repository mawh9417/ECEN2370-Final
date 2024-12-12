#include "Button_Driver.h"

void buttonInit()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef localStruct = {0};
	localStruct.Pin = USER_BUTTON_PIN;
	localStruct.Mode = GPIO_MODE_INPUT;
	localStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	localStruct.Pull = GPIO_NOPULL;
	localStruct.Alternate = 0;

	HAL_GPIO_Init(GPIOA, &localStruct);
}

void clockEnable()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
}

bool buttonPressed()
{
	//uint8_t returnval = GPIO_ReadFromInputPin(GPIOA, GPIOA_OFFSET);
	uint8_t returnval = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
	if (returnval == USER_BUTTON_PRESSED)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void initializeInterruptMode()
{
	GPIO_InitTypeDef localStruct2 = {0};
	//GPIO_PinConfig_t localStruct2 = {0};
	localStruct2.Pin = GPIO_PIN_0;
	localStruct2.Mode = GPIO_MODE_IT_RISING;
	localStruct2.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	localStruct2.Pull = GPIO_NOPULL;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(GPIOA, &localStruct2);
	HAL_NVIC_EnableIRQ(GPIOG_OFFSET);
	//HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
	//NVIC_ToggleGPIOPeripheral(EXTI0_IRQ_NUMBER, ENABLE);
}
