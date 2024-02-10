#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LightControllerSpy.h"
#include "LightController.h"
}

// clang-format off
TEST_GROUP(LightControllerSpy)
{
    void setup()
    {
        LightController_Create();
    }

    void teardown()
    {
        LightController_Destroy();
    }
};
// clang-format on

TEST(LightControllerSpy, Create)
{
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightControllerSpy, RememberTheLastLightIdControlled)
{
    LightController_On(10);
    LONGS_EQUAL(10, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());
}