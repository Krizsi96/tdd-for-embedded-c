#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#include <stdbool.h>
#include <stdint.h>

void LedDriver_Create(uint16_t *address);
void LedDriver_Destroy(void);
void LedDriver_TurnOn(int led_number);
void LedDriver_TurnOff(int led_number);
void LedDriver_TurnAllOn(void);
void LedDriver_TurnAllOff(void);
bool LedDriver_IsOn(int led_number);
bool LedDriver_IsOff(int led_number);

#endif  // LED_DRIVER_H_