/*
 * ApplicationCode.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Xavion
 */

#include "LCD_Driver.h"
#include "Button_Driver.h"
#include "stm32f4xx_hal.h"
#include "RNG.h"
#include "Scheduler.h"
#include "Game.h"
#include "Timer_Driver.h"

#include <stdio.h>
#include <stdbool.h>

#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_

void ApplicationInit(void);
void LCD_Visual_Demo(void);

void executeScreenPollRoutine();
bool LCD_Screen_Pressed();
void LCD_Screen_Pressed_Move();
uint32_t randomNum();
void buttonInterruptInit();

void EXTI0_IRQHandler();
void EXTI15_10_IRQHandler();

void Application_Execute_Game();

#if (COMPILE_TOUCH_FUNCTIONS == 1) && (COMPILE_TOUCH_INTERRUPT_SUPPORT == 0)
void LCD_Touch_Polling_Demo(void);
#endif // (COMPILE_TOUCH_FUNCTIONS == 1) && (COMPILE_TOUCH_INTERRUPT_SUPPORT == 0)

#endif /* INC_APPLICATIONCODE_H_ */
