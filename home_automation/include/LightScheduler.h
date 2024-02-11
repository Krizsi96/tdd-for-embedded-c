#ifndef LIGHT_SCHEDULER_H_
#define LIGHT_SCHEDULER_H_

#include "TimeService.h"

#define MAX_EVENTS 128

enum
{
    LS_OK,
    LS_TOO_MANY_EVENTS,
    LS_ID_OUT_OF_BOUNDS
};

enum Day
{
    NONE = -1,
    EVERYDAY = 10,
    WEEKDAY,
    WEEKEND,
    SUNDAY = 1,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
};

typedef enum Day Day;

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);
int LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay);
int LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay);
void LightScheduler_ScheduleRemove(int id, Day day, int minuteOfDay);
void LightScheduler_WakeUp(void);

#endif // LIGHT_SCHEDULER_H_