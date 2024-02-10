#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LightScheduler.h"
#include "LightControllerSpy.h"
#include "FakeTimeService.h"
}

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
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, NoScheduleNothingHappens)
{
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(100);
    LightScheduler_WakeUp();
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
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