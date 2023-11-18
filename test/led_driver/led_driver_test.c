#include "led_driver.h"

#include "unity_fixture.h"

TEST_GROUP(LedDriver);

TEST_SETUP(LedDriver) {}

TEST_TEAR_DOWN(LedDriver) {}

// LED Driver Tests
// All LEDS are off after the driver is intitialized
TEST(LedDriver, LedsOffAfterCreate) {
  uint16_t virtual_leds = 0xffff;
  LedDriver_Create(&virtual_leds);
  TEST_ASSERT_EQUAL_HEX16(0, virtual_leds);
}

// A single LED can be turned on
// A single LED can be turned off
// Multiple LEDs can be turned on/off
// Turn on all LEDs
// Turn off all LEDs
// Query LED state
// Check boundary values
// Check out-of-bounds values