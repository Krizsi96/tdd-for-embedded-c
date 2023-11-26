#include "led_driver.h"

#include "runtime_error_stub.h"
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

// Driver should not write out-of-bounds
TEST(LedDriver, UpperAndLowerBounds) {
  LedDriver_TurnOn(1);
  LedDriver_TurnOn(16);
  TEST_ASSERT_EQUAL_HEX16(0x8001, virtual_leds);
}

TEST(LedDriver, OutOfBoundsTurnOnDoesNoHarm) {
  LedDriver_TurnOn(-1);
  LedDriver_TurnOn(0);
  LedDriver_TurnOn(17);
  LedDriver_TurnOn(3141);
  TEST_ASSERT_EQUAL_HEX16(0, virtual_leds);
}

TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm) {
  LedDriver_TurnAllOn();
  LedDriver_TurnOff(-1);
  LedDriver_TurnOff(0);
  LedDriver_TurnOff(17);
  LedDriver_TurnOff(3141);
  TEST_ASSERT_EQUAL_HEX16(0xffff, virtual_leds);
}

TEST(LedDriver, OutOfBoundsProducesRuntimeError) {
  LedDriver_TurnOn(-1);
  TEST_ASSERT_EQUAL_STRING("LED Driver: out-of-bounds LED",
                           RuntimeErrorStub_GetLastError());
  TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}

// Turn off all LEDs
// Query LED state
// Check boundary values
// Check out-of-bounds values