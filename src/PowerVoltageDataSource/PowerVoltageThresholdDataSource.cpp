#include "PowerVoltageDataSource/PowerVoltageThresholdDataSource.hpp"

#define VOLTAGE_LEVEL_WARNING 2320
#define VOLTAGE_LEVEL_ERROR 2200

bool PowerVoltageThresholdDataSource::initializeDataSource()
{
    return true;
}

String PowerVoltageThresholdDataSource::getDataString()
{
    const uint16_t currentVoltage = ESP.getVcc();

    if (currentVoltage > VOLTAGE_LEVEL_WARNING)
    {
        return String(2);
    }
    else if ((currentVoltage < VOLTAGE_LEVEL_WARNING) && (currentVoltage > VOLTAGE_LEVEL_ERROR))
    {
        return String(1);
    }
    else
    {
        return String(0);
    }
}