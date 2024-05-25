#ifndef FAKEMICROTIME_H_
#define FAKEMICROTIME_H_

#include "MicroTime.h"
#include <stdint.h>

void FakeMicroTime_Init(uint32_t start, uint32_t incr);

#endif // FAKEMICROTIME_H_