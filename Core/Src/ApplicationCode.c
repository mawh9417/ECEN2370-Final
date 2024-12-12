/*
 * ApplicationCode.c
 *
 *  Created on: Dec 30, 2023 (updated 11/12/2024) Thanks Donavon! 
 *      Author: Xavion
 */

#include "ApplicationCode.h"

/* Static variables */

#define SHAPE_ONE_HLIMIT	24

extern void initialise_monitor_handles(void); 

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#if TOUCH_INTERRUPT_ENABLED == 1
static EXTI_HandleTypeDef LCDTouchIRQ;
void LCDTouchScreenInterruptGPIOInit(void);
#endif // TOUCH_INTERRUPT_ENABLED
#endif // COMPILE_TOUCH_FUNCTIONS

void ApplicationInit(void)
{
	initialise_monitor_handles(); // Allows printf functionality
    LTCD__Init();
    LTCD_Layer_Init(0);
    RNG_Init();
    TIM2_Init();
    buttonInterruptInit();
    LCD_Clear(0,LCD_COLOR_WHITE);
    #if COMPILE_TOUCH_FUNCTIONS == 1
	InitializeLCDTouch();

	// This is the orientation for the board to be direclty up where the buttons are vertically above the screen
	// Top left would be low x value, high y value. Bottom right would be low x value, low y value.
	StaticTouchData.orientation = STMPE811_Orientation_Portrait_2;

	#if TOUCH_INTERRUPT_ENABLED == 1
	LCDTouchScreenInterruptGPIOInit();
	#endif // TOUCH_INTERRUPT_ENABLED

	#endif // COMPILE_TOUCH_FUNCTIONS
}

uint32_t randonNum()
{
	return generateRandomNum();
}

void LCD_Visual_Demo(void)
{
	visualDemo();
}

void Application_Execute_Game()
{
	executeGame();
}

#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_Touch_Polling_Demo(void)
{
	LCD_Clear(0,LCD_COLOR_GREEN);
	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			LCD_Clear(0, LCD_COLOR_RED);
		} else {
			/* Touch not pressed */
			printf("Not Pressed\n\n");
			LCD_Clear(0, LCD_COLOR_GREEN);
		}
	}
}

bool LCD_Screen_Pressed()
{
	while (1)
	{
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			return true;
		} else {
			/* Touch not pressed */
			return false;
		}
	}
}

void buttonInterruptInit()
{
	initializeInterruptMode();
}

// TouchScreen Interrupt
#if TOUCH_INTERRUPT_ENABLED == 1

void LCDTouchScreenInterruptGPIOInit(void)
{
	GPIO_InitTypeDef LCDConfig = {0};
    LCDConfig.Pin = GPIO_PIN_15;
    LCDConfig.Mode = GPIO_MODE_IT_RISING_FALLING;
    LCDConfig.Pull = GPIO_NOPULL;
    LCDConfig.Speed = GPIO_SPEED_FREQ_HIGH;
    
    // Clock enable
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // GPIO Init      
    HAL_GPIO_Init(GPIOA, &LCDConfig);

    // Interrupt Configuration
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	LCDTouchIRQ.Line = EXTI_LINE_15;
}

int game_start = 0;

#define TOUCH_DETECTED_IRQ_STATUS_BIT   (1 << 0)  // Touchscreen detected bitmask

static uint8_t statusFlag;

int tracker_num = 0;


////////////// ALL INTERRUPT HANDLERS BELOW //////////////


void EXTI15_10_IRQHandler()
{
	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn); // May consider making this a universial interrupt guard
	bool isTouchDetected = false;

	static uint32_t count;
	count = 0;
	while(count == 0){
		count = STMPE811_Read(STMPE811_FIFO_SIZE);
	}

	// Disable touch interrupt bit on the STMPE811
	uint8_t currentIRQEnables = ReadRegisterFromTouchModule(STMPE811_INT_EN);
	WriteDataToTouchModule(STMPE811_INT_EN, 0x00);

	// Clear the interrupt bit in the STMPE811
	statusFlag = ReadRegisterFromTouchModule(STMPE811_INT_STA);
	uint8_t clearIRQData = (statusFlag | TOUCH_DETECTED_IRQ_STATUS_BIT); // Write one to clear bit
	WriteDataToTouchModule(STMPE811_INT_STA, clearIRQData);
	
	uint8_t ctrlReg = ReadRegisterFromTouchModule(STMPE811_TSC_CTRL);
	if (ctrlReg & 0x80)
	{
		isTouchDetected = true;
	}
	// Determine if it is pressed or unpressed
	if(isTouchDetected) // Touch has been detected
	{
		if (game_start == 0) // skips once cycle of the move process to allow for menu operation
		{
			LCD_Clear(0, LCD_COLOR_WHITE);
			addSchedulerEvent(GAME_EVENT);
			for (int i = 312; i <= 319; i++) {
				LCD_Draw_Horizontal_Line(0, i, 240, LCD_COLOR_BLACK);
			}
			TIM2_Start();
			game_start++;
		}
		else if (game_start >= 1)
		{
			uint8_t touchLocation = ReadRegisterFromTouchModule(STMPE811_TSC_DATA_X);
			printf("X_Data Register: %d", touchLocation);
			if (touchLocation > 60) // right side screen touched
			{
				moveOneLeft();
			}
			else if (touchLocation <= 60) // left side screen touched
			{
				moveOneRight();
			}
		}
	}

	STMPE811_Write(STMPE811_FIFO_STA, 0x01);
	STMPE811_Write(STMPE811_FIFO_STA, 0x00);

	// Re-enable IRQs
    WriteDataToTouchModule(STMPE811_INT_EN, currentIRQEnables);
	HAL_EXTI_ClearPending(&LCDTouchIRQ, EXTI_TRIGGER_RISING_FALLING);

	HAL_NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	//Potential ERRATA? Clearing IRQ bit again due to an IRQ being triggered DURING the handling of this IRQ..
	WriteDataToTouchModule(STMPE811_INT_STA, clearIRQData);
}
#endif // TOUCH_INTERRUPT_ENABLED
#endif // COMPILE_TOUCH_FUNCTIONS

// need EXTI controller for each PA# (EXTI#...)

void EXTI0_IRQHandler()
{
	EXTI_HandleTypeDef localStruct = {0};
	localStruct.Line = EXTI_LINE_0;
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	HAL_NVIC_ClearPendingIRQ(EXTI0_IRQn);
	HAL_EXTI_ClearPending(&localStruct, EXTI_TRIGGER_RISING);
	rotateShape();
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

int time_seconds = 0;

void TIM2_IRQHandler()
{
	HAL_NVIC_DisableIRQ(TIM2_IRQn);
	HAL_NVIC_ClearPendingIRQ(TIM2_IRQn);
	time_seconds ++;
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}
