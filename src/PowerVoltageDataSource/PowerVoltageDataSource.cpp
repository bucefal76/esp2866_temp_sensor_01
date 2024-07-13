#include "PowerVoltageDataSource/PowerVoltageDataSource.hpp"

bool PowerVoltageDataSource::initializeDataSource()
{
    return true;
}

String PowerVoltageDataSource::getDataString()
{
    const uint16_t currentVoltage = ESP.getVcc();
    return String(currentVoltage);
}
