#include "LightControllerSpy.h"
#include "LightController.h"
#include <stdbool.h>

static int lastId;
static int lastState;
static int light_states[128];

static int isIdInRange(int id);

void LightController_Create(void)
{
    lastId = LIGHT_ID_UNKNOWN;
    lastState = LIGHT_STATE_UNKNOWN;
    for (int i = 0; i < 128; i++)
        light_states[i] = LIGHT_STATE_UNKNOWN;
}

void LightController_Destroy(void)
{
}

void LightController_On(int id)
{
    lastId = id;
    lastState = LIGHT_ON;
    if (isIdInRange(id))
        light_states[id] = LIGHT_ON;
}

void LightController_Off(int id)
{
    lastId = id;
    lastState = LIGHT_OFF;
    if (isIdInRange(id))
        light_states[id] = LIGHT_OFF;
}

int LightControllerSpy_GetLastId(void)
{
    return lastId;
}

int LightControllerSpy_GetLastState(void)
{
    return lastState;
}

int LightControllerSpy_GetLightState(int id)
{
    if (!isIdInRange(id))
        return LIGHT_STATE_UNKNOWN;

    return light_states[id];
}

static int isIdInRange(int id)
{
    if (0 <= id && id < 127)
        return true;
    return false;
}