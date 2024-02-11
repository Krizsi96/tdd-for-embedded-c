#include "LightScheduler.h"
#include "TimeService.h"
#include "LightController.h"
#include <stdbool.h>

#define MIN_LIGHT_ID 0
#define MAX_LIGHT_ID 31

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

static ScheduledLightEvent scheduledEvents[MAX_EVENTS];

static int scheduleEvent(int id, Day day, int minuteOfDay, int event);
static void processEventDueNow(Time *time, ScheduledLightEvent *lightEvent);
static void operateLight(ScheduledLightEvent *lightEvent);
static int doesLightRespondToday(Time *time, int reactionDay);
static int isValidId(int id);

void LightScheduler_Create(void)
{
    for (int i = 0; i < MAX_EVENTS; i++)
        scheduledEvents[i].id = UNUSED;
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

    for (int i = 0; i < MAX_EVENTS; i++)
        processEventDueNow(&time, &scheduledEvents[i]);
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

int LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
    return scheduleEvent(id, day, minuteOfDay, TURN_ON);
}

int LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
    return scheduleEvent(id, day, minuteOfDay, TURN_OFF);
}

static int scheduleEvent(int id, Day day, int minuteOfDay, int event)
{
    if (!isValidId(id))
        return LS_ID_OUT_OF_BOUNDS;
    for (int i = 0; i < MAX_EVENTS; i++)
    {
        if (scheduledEvents[i].id == UNUSED)
        {
            scheduledEvents[i].day = day;
            scheduledEvents[i].minuteOfDay = minuteOfDay;
            scheduledEvents[i].event = event;
            scheduledEvents[i].id = id;
            return LS_OK;
        }
    }
    return LS_TOO_MANY_EVENTS;
}

static int isValidId(int id)
{
    if (MIN_LIGHT_ID <= id && id <= MAX_LIGHT_ID)
        return true;
    return false;
}

void LightScheduler_ScheduleRemove(int id, Day day, int minuteOfDay)
{
    for (int i = 0; i < MAX_EVENTS; i++)
    {
        int event_id = scheduledEvents[i].id;
        Day event_day = scheduledEvents[i].day;
        int event_minuteOfDay = scheduledEvents[i].minuteOfDay;

        if (event_id == id && event_day == day && event_minuteOfDay == minuteOfDay)
            scheduledEvents[i].id = UNUSED;
    }
}