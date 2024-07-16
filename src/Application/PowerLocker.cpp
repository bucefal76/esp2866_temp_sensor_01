#include "Application/PowerLocker.hpp"

#include <Arduino.h>
#include "ModuleConfig.hpp"

PowerLocker::PowerLocker()
{

    const uint16_t currentVoltage = ESP.getVcc();

    if (currentVoltage < VOLTAGE_LEVEL_ERROR)
    {
#ifdef APPLICATION_USE_DEEP_SLEEP

#ifdef USE_SERIAL
        Serial.println(F("Power to low, going to the deep sleep forever..."));
#endif
        ESP.deepSleep(0xFFFFFFFFFFFFFFFF);
#endif
    }
}