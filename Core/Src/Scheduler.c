#include "Scheduler.h"

static uint32_t scheduledEvents;

int getScheduledEvents()
{
	return scheduledEvents;
}

void addSchedulerEvent(uint32_t event_scheduled)
{
	scheduledEvents |= (event_scheduled);
}

void removeSchedulerEvent(uint32_t remove_event)
{
	scheduledEvents &= ~(remove_event);
}
