#ifndef TIMESERVICE_H_
#define TIMESERVICE_H_

typedef struct
{
    int minuteOfDay;
    int dayOfWeek;
} Time;

typedef void (*WakeUpCallback)(void);

void TimeService_GetTime(Time *time);
void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeUpCallback);
void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeUpCallback);

#endif // TIMESERVICE_H_