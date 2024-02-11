#include "FakeTimeService.h"

static Time fakeTime;
static WakeUpCallback callback;
static int period;

void TimeService_GetTime(Time *time)
{
    time->minuteOfDay = fakeTime.minuteOfDay;
    time->dayOfWeek = fakeTime.dayOfWeek;
};

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeUpCallback cb)
{
    callback = cb;
    period = seconds;
}

void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeUpCallback cb)
{
    if (cb == callback && period == seconds)
    {
        callback = 0;
        period = 0;
    }
}

void FakeTimeService_Create(void)
{
    fakeTime.minuteOfDay = TIME_UNKNOWN;
    fakeTime.dayOfWeek = TIME_UNKNOWN;
};

void FakeTimeService_Destroy(void)
{
    fakeTime.dayOfWeek = TIME_UNKNOWN;
    fakeTime.minuteOfDay = TIME_UNKNOWN;
};

void FakeTimeService_SetMinute(int minute)
{
    fakeTime.minuteOfDay = minute;
};

void FakeTimeService_SetDay(int day)
{
    fakeTime.dayOfWeek = day;
};

WakeUpCallback FakeTimeService_GetAlarmCallback()
{
    return callback;
};

int FakeTimeService_GetAlarmPeriod()
{
    return period;
};