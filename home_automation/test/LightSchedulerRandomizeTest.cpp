#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LightScheduler.h"
#include "LightController.h"
#include "RandomMinute.h"
#include "LightControllerSpy.h"
#include "FakeTimeService.h"
}

// clang-format off
TEST_GROUP(LightSchedulerRandomize)
{
    void setup()
    {
        LightController_Create();
        LightScheduler_Create();
        UT_PTR_SET(RandomMinute_Get, FakeRandomMinute_Get);
    }

    void teardown()
    {
        LightScheduler_Destroy();
        LightController_Destroy();
    }

    void checkLightState(int id, int level)
    {
        if (id == LIGHT_ID_UNKNOWN)
        {
            LONGS_EQUAL(id, LightControllerSpy_GetLastId());
            LONGS_EQUAL(level, LightControllerSpy_GetLastState());
        }
        else 
            LONGS_EQUAL(level, LightControllerSpy_GetLightState(id));
    }

    void setTimeTo(int day, int minute)
    {
        FakeTimeService_SetDay(day);
        FakeTimeService_SetMinute(minute);
    }
};
// clang-format on

TEST(LightSchedulerRandomize, TurnsOnEarly)
{
    FakeRandomMinute_SetFirstAndIncrement(-10, 5);
    LightScheduler_ScheduleTurnOn(4, EVERYDAY, 600);
    LightScheduler_Randomize(4, EVERYDAY, 600);
    setTimeTo(MONDAY, 600 - 10);
    LightScheduler_WakeUp();
    checkLightState(4, LIGHT_ON);
}