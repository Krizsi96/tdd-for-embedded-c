#ifndef FAKE_TIME_SERVICE_H_
#define FAKE_TIME_SERVICE_H_

#include "TimeService.h"

enum
{
    TIME_UNKNOWN = -1
};

void FakeTimeService_Create(void);
void FakeTimeService_Destroy(void);
WakeUpCallback FakeTimeService_GetAlarmCallback();
int FakeTimeService_GetAlarmPeriod();
void FakeTimeService_SetMinute(int);
void FakeTimeService_SetDay(int);

#endif // FAKE_TIME_SERVICE_H_