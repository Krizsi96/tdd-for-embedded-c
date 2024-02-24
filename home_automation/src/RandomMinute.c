#include "RandomMinute.h"

static int bound;

void RandomMinute_Create(int bound) {}

int RandomMinute_GetImpl(void)
{
    return bound - rand() % (bound * 2 + 1);
}

int (*RandomMinute_Get)(void) = RandomMinute_GetImpl;