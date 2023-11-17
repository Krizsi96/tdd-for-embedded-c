#include "unity_fixture.h"

TEST_GROUP(LedDriver);

TEST_SETUP(LedDriver) {}

TEST_TEAR_DOWN(LedDriver) {}

TEST(LedDriver, LedsOffAfterCreate) { TEST_FAIL_MESSAGE("Start here"); }

// LED Driver Tests
// All LEDS are off after the driver is intitialized
// A single LED can be turned on
// A single LED can be turned off
// Multiple LEDs can be turned on/off
// Turn on all LEDs
// Turn off all LEDs
// Query LED state
// Check boundary values
// Check out-of-bounds values