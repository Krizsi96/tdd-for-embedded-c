#include "led_driver.h"

#include "unity_fixture.h"

TEST_GROUP(LedDriver);
static uint16_t virtual_leds;
TEST_SETUP(LedDriver) { LedDriver_Create(&virtual_leds); }

TEST_TEAR_DOWN(LedDriver) {}

// LED Driver Tests
TEST(LedDriver, LedsOffAfterCreate) {
  uint16_t virtual_leds = 0xffff;
  LedDriver_Create(&virtual_leds);
  TEST_ASSERT_EQUAL_HEX16(0, virtual_leds);
}

// A single LED can be turned on
TEST(LedDriver, TurnOnLedOne) {
  LedDriver_TurnOn(1);
  TEST_ASSERT_EQUAL_HEX16(1, virtual_leds);
}

// A single LED can be turned off
TEST(LedDriver, TurnOffLedOne) {
  LedDriver_TurnOn(1);
  LedDriver_TurnOff(1);
  TEST_ASSERT_EQUAL_HEX16(0, virtual_leds);
}

// Multiple LEDs can be turned on/off
TEST(LedDriver, TurnOnMultipleLeds) {
  LedDriver_TurnOn(9);
  LedDriver_TurnOn(8);
  TEST_ASSERT_EQUAL_HEX16(0x180, virtual_leds);
}

TEST(LedDriver, TurnOffAnyLed) {
  LedDriver_TurnAllOn();
  LedDriver_TurnOff(8);
  TEST_ASSERT_EQUAL_HEX16(0xff7f, virtual_leds);
}

// Turn on all LEDs
TEST(LedDriver, AllOn) {
  LedDriver_TurnAllOn();
  TEST_ASSERT_EQUAL_HEX16(0xffff, virtual_leds);
}

// Driver should not use the LED memory location for reading
TEST(LedDriver, LedMemoryIsNotReadable) {
  virtual_leds = 0xffff;
  LedDriver_TurnOn(8);
  TEST_ASSERT_EQUAL_HEX16(0x80, virtual_leds);
}

// Turn off all LEDs
// Query LED state
// Check boundary values
// Check out-of-bounds values