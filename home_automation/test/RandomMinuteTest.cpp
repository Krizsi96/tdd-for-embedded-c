#include "CppUTest/TestHarness.h"

extern "C"
{
#include "RandomMinute.h"
}

enum
{
    BOUND = 30
};

// clang-format off
TEST_GROUP(RandomMinute)
{
    int minute;
    void setup()
    {
        RandomMinute_Create(BOUND);
        srand(1);
    }
    void AssertMinuteIsInRange()
    {
        if (minute < -BOUND || minute > BOUND)
        {
            printf("bad minute value: %d\n", minute);
            FAIL("Minute out of range");
        }
    }
};
// clang-format on

TEST(RandomMinute, GetIsInRange)
{
    for (int i = 0; i < 100; i++)
    {
        minute = RandomMinute_Get();
        AssertMinuteIsInRange();
    }
}

TEST(RandomMinute, AllValuesPossible)
{
    int hit[2 * BOUND + 1];
    memset(hit, 0, sizeof(hit));
    for (int i = 0; i < 300; i++)
    {
        minute = RandomMinute_Get();
        AssertMinuteIsInRange();
        hit[minute + BOUND]++;
    }
    for (int i = 0; i < 2 * BOUND + 1; i++)
    {
        CHECK(hit[i] > 0);
    }
}