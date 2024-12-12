#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_

#include <stdbool.h>
#include "stm32f4xx_hal.h"

// user button - port GPIOA 0 (PA0)

#define USER_BUTTON_PORT 		0
#define USER_BUTTON_PIN 		0
#define USER_BUTTON_PRESSED 	1
#define USER_BUTTON_NOT_PRESSED 0
#define GPIOG_OFFSET			6
#define BUTTON_1_PIN 			1
#define BUTTON_2_PIN 			2
#define BUTTON_3_PIN			3
#define BUTTON_4_PIN			4

void buttonInit();

void clockEnable();

bool buttonPressed();

void initializeInterruptMode();

#endif
