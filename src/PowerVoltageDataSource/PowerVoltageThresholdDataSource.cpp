#include "PowerVoltageDataSource/PowerVoltageThresholdDataSource.hpp"
#include "ModuleConfig.hpp"

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