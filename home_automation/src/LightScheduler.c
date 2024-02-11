#include "LightScheduler.h"
#include "TimeService.h"
#include "LightController.h"

typedef struct
{
    int id;
    int minuteOfDay;
    int event;
} ScheduledLightEvent;

enum
{
    UNUSED = -1
};

enum
{
    TURN_ON,
    TURN_OFF
};

static ScheduledLightEvent scheduledEvent;
static void scheduleEvent(int id, Day day, int minuteOfDay, int event);
static void processEventDueNow(Time *time, ScheduledLightEvent *lightEvent);
static void operateLight(ScheduledLightEvent *lightEvent);

void LightScheduler_Create(void)
{
    scheduledEvent.id = UNUSED;
}

void LightScheduler_Destroy(void)
{
}

void LightScheduler_WakeUp(void)
{
    Time time;
    TimeService_GetTime(&time);

    processEventDueNow(&time, &scheduledEvent);
}

static void processEventDueNow(Time *time, ScheduledLightEvent *lightEvent)
{
    if (lightEvent->id == UNUSED)
        return;

    if (lightEvent->minuteOfDay != time->minuteOfDay)
        return;

    operateLight(lightEvent);
}

static void operateLight(ScheduledLightEvent *lightEvent)
{
    if (lightEvent->event == TURN_ON)
        LightController_On(lightEvent->id);
    else if (lightEvent->event == TURN_OFF)
        LightController_Off(lightEvent->id);
}

void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
    scheduleEvent(id, day, minuteOfDay, TURN_ON);
}

void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
    scheduleEvent(id, day, minuteOfDay, TURN_OFF);
}

static void scheduleEvent(int id, Day day, int minuteOfDay, int event)
{
    scheduledEvent.minuteOfDay = minuteOfDay;
    scheduledEvent.event = event;
    scheduledEvent.id = id;
}