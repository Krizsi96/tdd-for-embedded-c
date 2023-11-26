#include "led_driver.h"

enum { kAllLedsOn = ~0, kAllLedsOff = ~kAllLedsOn };

static uint16_t *leds_address;
static uint16_t leds_image;

static uint16_t ConvertLedNumberToBit(int led_number);
static void UpdateHardware(void);

void LedDriver_Create(uint16_t *address) {
  leds_address = address;
  leds_image = kAllLedsOff;
  UpdateHardware();
}

void LedDriver_Destroy(void) {}

void LedDriver_TurnOn(int led_number) {
  leds_image |= ConvertLedNumberToBit(led_number);
  UpdateHardware();
}

void LedDriver_TurnOff(int led_number) {
  leds_image &= ~(ConvertLedNumberToBit(led_number));
  UpdateHardware();
}

void LedDriver_TurnAllOn(void) {
  leds_image = kAllLedsOn;
  UpdateHardware();
}

static uint16_t ConvertLedNumberToBit(int led_number) {
  return 1 << (led_number - 1);
}

static void UpdateHardware(void) { *leds_address = leds_image; }