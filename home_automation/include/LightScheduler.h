#ifndef LIGHT_SCHEDULER_H_
#define LIGHT_SCHEDULER_H_

#include "TimeService.h"

typedef enum
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
} Day;

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);
void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay);
void LightScheduler_WakeUp(void);

#endif // LIGHT_SCHEDULER_H_