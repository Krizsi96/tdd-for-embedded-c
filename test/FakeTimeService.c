#include "FakeTimeService.h"

static Time fakeTime;

void TimeService_GetTime(Time *time)
{
    time->minuteOfDay = fakeTime.minuteOfDay;
    time->dayOfWeek = fakeTime.dayOfWeek;
};

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
