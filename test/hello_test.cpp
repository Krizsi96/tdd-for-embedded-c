#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

TEST_GROUP(FirstTestGroup){};

TEST(FirstTestGroup, FirstTest)
{
    CHECK(true);
}

int main(int ac, char **av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
