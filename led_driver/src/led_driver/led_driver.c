#include "led_driver.h"

#include "runtime_error.h"

enum { kAllLedsOn = ~0, kAllLedsOff = ~kAllLedsOn };
enum { kFirstLed = 1, kLastLed = 16 };

static uint16_t *leds_address;
static uint16_t leds_image;

static uint16_t ConvertLedNumberToBit(int led_number);
static void UpdateHardware(void);
static bool IsLedOutOfBounds(int led_number);
static void SetLedImageBit(int led_number);
static void ClearLedImageBit(int led_number);

void LedDriver_Create(uint16_t *address) {
  leds_address = address;
  leds_image = kAllLedsOff;
  UpdateHardware();
}

void LedDriver_Destroy(void) {}

void LedDriver_TurnOn(int led_number) {
  if (IsLedOutOfBounds(led_number)) {
    RUNTIME_ERROR("LED Driver: out-of-bounds LED", -1);
    return;
  }
  SetLedImageBit(led_number);
  UpdateHardware();
}

void LedDriver_TurnOff(int led_number) {
  if (IsLedOutOfBounds(led_number)) return;
  ClearLedImageBit(led_number);
  UpdateHardware();
}

void LedDriver_TurnAllOn(void) {
  leds_image = kAllLedsOn;
  UpdateHardware();
}

void LedDriver_TurnAllOff(void) {
  leds_image = kAllLedsOff;
  UpdateHardware();
}

bool LedDriver_IsOn(int led_number) {
  if (IsLedOutOfBounds(led_number)) return false;
  return leds_image & (ConvertLedNumberToBit(led_number));
}

bool LedDriver_IsOff(int led_number) { return !LedDriver_IsOn(led_number); }

static uint16_t ConvertLedNumberToBit(int led_number) {
  return 1 << (led_number - 1);
}

static void UpdateHardware(void) { *leds_address = leds_image; }

static bool IsLedOutOfBounds(int led_number) {
  bool is_out_of_bounds = false;
  if (led_number < kFirstLed || led_number > kLastLed) is_out_of_bounds = true;
  return is_out_of_bounds;
}

static void SetLedImageBit(int led_number) {
  leds_image |= ConvertLedNumberToBit(led_number);
}

static void ClearLedImageBit(int led_number) {
  leds_image &= ~(ConvertLedNumberToBit(led_number));
}
