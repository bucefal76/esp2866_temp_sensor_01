#include "PowerVoltageDataSource.hpp"

bool PowerVoltageDataSource::initializeDataSource()
{
    return true;
}

String PowerVoltageDataSource::getDataString()
{
    const uint16_t currentVoltage = ESP.getVcc();

    // const float mappedVolatege = map(currentVoltage, 0, 2800, 0, 3200);

    // Serial.print("System voltage(mV): ");
    // Serial.println(mappedVolatege);

    return String(currentVoltage);
}
