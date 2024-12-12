#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

#include "stm32f4xx_hal.h"

#define CDRATIO1 0
#define CDRATIO2 1
#define CDRATIO3 2

#define EDGEALIGNEDMODE 	0
#define CENTERALIGNEDMODE 	1
#define CENTERALIGNEDMODE2 	2
#define CENTERALIGNEDMODE3	3

#define MMRESET 		0
#define MMENABLE 		1
#define MMUPDATE 		2
#define MMCOMPAREPULSE	3
#define MMOC1REF 		4
#define MMOC2REF 		5
#define MMOC3REF 		6
#define MMOC4REF		7

#define ARBENABLE_TRUE 			1
#define ARBENABLE_FALSE 		0

#define UPDATE_EVENT_ENABLE 	1
#define UPDATE_EVENT_DISABLE	0

#define CR1_CEN_OFFSET 		0
#define CR1_UDIS_OFFSET 	1
#define CR1_URS_OFFSET		2
#define CR1_OPM_OFFSET		3
#define CR1_DIR_OFFSET		4
#define CR1_CMS_OFFSET 		5
#define CR1_ARPE_OFFSET 	6
#define CR1_CKD_OFFSET 		7
#define DIER_UIE_OFFSET 	0
#define CR2_MMS_OFFSET 		4

#define OMP_ENABLE 		1
#define OMP_DISABLE 	0

#define ARP_BUFFERED		1
#define ARP_NOT_BUFFERED 	0

#define UP_COUNTER 		0
#define DOWN_COUNTER	1

#define NO_INTERRUPT_UPDATE		0
#define INTERRUPT_UPDATE_PEND 	1

void TIM6_Init();

void TIM6_Start();

void TIM6_Stop();

#endif
