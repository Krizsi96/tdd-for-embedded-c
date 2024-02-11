#include "LightScheduler.h"
#include "TimeService.h"
#include "LightController.h"
#include <stdbool.h>

typedef struct
{
    int id;
    int minuteOfDay;
    Day day;
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
static int doesLightRespondToday(Time *time, int reactionDay);

void LightScheduler_Create(void)
{
    scheduledEvent.id = UNUSED;

    TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
}

void LightScheduler_Destroy(void)
{
    TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
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
    if (!doesLightRespondToday(time, lightEvent->day))
        return;
    if (lightEvent->minuteOfDay != time->minuteOfDay)
        return;

    operateLight(lightEvent);
}

static int doesLightRespondToday(Time *time, int reactionDay)
{
    int today = time->dayOfWeek;

    if (reactionDay == EVERYDAY)
        return true;

    if (reactionDay == today)
        return true;

    if (reactionDay == WEEKEND && (SATURDAY == today || SUNDAY == today))
        return true;

    if (reactionDay == WEEKDAY && today >= MONDAY && today <= FRIDAY)
        return true;

    return false;
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
    scheduledEvent.day = day;
    scheduledEvent.minuteOfDay = minuteOfDay;
    scheduledEvent.event = event;
    scheduledEvent.id = id;
}