#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdint.h>

#define LED_TOGGLE_EVENT	(1 << 0)
#define DELAY_EVENT			(1 << 1)
#define SCREEN_POLL_EVENT 	(1 << 2)
#define GAME_EVENT			(1 << 3)

int getScheduledEvents();

void addSchedulerEvent(uint32_t event_scheduled);

void removeSchedulerEvent(uint32_t remove_event);

#endif
