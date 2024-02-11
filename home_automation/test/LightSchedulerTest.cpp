#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LightScheduler.h"
#include "LightControllerSpy.h"
#include "FakeTimeService.h"
}

void setTimeTo(int day, int minuteOfDay);
void checkLightState(int id, int level);

// clang-format off
TEST_GROUP(LightScheduler)
{
    void setup(){
        LightController_Create();
        LightScheduler_Create();
    }

    void teardown()
    {
        LightScheduler_Destroy();
        LightController_Destroy();
    }
};
// clang-format on

// TEST(LightScheduler, ScheduleOnEverydayNotTimeYet)
// {
//     LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
//     FakeTimeService_SetDay(MONDAY);
//     FakeTimeService_SetMinute(1199);
//     LightScheduler_WakeUp();

//     LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
//     LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightcontrollerSpy_GetLastState());
// }

TEST(LightScheduler, NoChangeToLightsDuringInitialization)
{
    LightScheduler_Create();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, NoScheduleNothingHappens)
{
    setTimeTo(MONDAY, 100);

    LightScheduler_WakeUp();

    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleONEverydayItsTime)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1200);

    LightScheduler_WakeUp();

    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOffEverydayItsTime)
{
    LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1200);

    LightScheduler_WakeUp();

    checkLightState(3, LIGHT_OFF);
}

TEST(LightScheduler, ScheduleTuesdayButItsMonday)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_WakeUp();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleTuesdayAndItsTuesday)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(TUESDAY, 1200);
    LightScheduler_WakeUp();
    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekEndItsFriday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(FRIDAY, 1200);
    LightScheduler_WakeUp();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleWeekEndItsSaturday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SATURDAY, 1200);
    LightScheduler_WakeUp();
    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekEndItsSunday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SUNDAY, 1200);
    LightScheduler_WakeUp();
    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekEndItsMonday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_WakeUp();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST_GROUP(LightSchedulerInitAndCleanup){};

TEST(LightSchedulerInitAndCleanup, createStartsOneMinuteAlarm)
{
    LightScheduler_Create();
    POINTERS_EQUAL((void *)LightScheduler_WakeUp, (void *)FakeTimeService_GetAlarmCallback());
    LONGS_EQUAL(60, FakeTimeService_GetAlarmPeriod());
    LightScheduler_Destroy();
}

TEST(LightSchedulerInitAndCleanup, DestroyCancelsOneMinuteAlarm)
{
    LightScheduler_Create();
    LightScheduler_Destroy();
    POINTERS_EQUAL(NULL, (void *)FakeTimeService_GetAlarmCallback());
}

// Lights are not change at initialization
// Time is wrong, day is wrong, no light are changed
// Day is right, time is wrong, no light are changed
// Day is wrong, time is right, no lights are changed
// Day is right, time is right, the right light is turned on
// Day is right, time is right, the right light is turned off
// Schedule eveyday
// Schedule a specific day
// Schedule all weedays
// Schedule weekend days
// Remove scheduled event
// Remove non-existent event
// Multiple scheduled events at the same time
// Multiple scheduled events for the same light
// Remove non scheduled light schedule
// Schedule the maximum supported number of events (128)
// Schedule too many events

void setTimeTo(int day, int minuteOfDay)
{
    FakeTimeService_SetDay(day);
    FakeTimeService_SetMinute(minuteOfDay);
}

void checkLightState(int id, int level)
{
    LONGS_EQUAL(id, LightControllerSpy_GetLastId());
    LONGS_EQUAL(level, LightControllerSpy_GetLastState());
}