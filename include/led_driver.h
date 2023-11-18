#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#include <stdint.h>

void LedDriver_Create(uint16_t *address);
void LedDriver_Destroy(void);

#endif  // LED_DRIVER_H_