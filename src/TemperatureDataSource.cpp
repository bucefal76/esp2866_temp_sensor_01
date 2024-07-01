#include <OneWire.h>
#include <DallasTemperature.h>

#include "TemperatureDataSource.hpp"
#include "ModuleConfig.hpp"

#define TEMPERATURE_PRECISION 9

OneWire oneWire(SENSOR_ONE_WIRE_INPUT);
DallasTemperature sensors(&oneWire);

void printAddress(DeviceAddress deviceAddress)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (deviceAddress[i] < 16)
            Serial.print("0");
        Serial.print(deviceAddress[i], HEX);
    }
}

bool TemperatureDataSource::initialize()
{
    sensors.begin();

    if (sensors.getDS18Count() > 0)
    {
        // sensors.requestTemperatures();

        return true;
    }
    else
    {
        return false;
    }
}

size_t TemperatureDataSource::getNumberOfSources() const
{
    return sensors.getDS18Count();
}

String TemperatureDataSource::getStrValueOfTheSource(const uint8_t dataSourceId) const
{
    if (0 == dataSourceId)
    {
        sensors.requestTemperatures();
        float temperatureC = sensors.getTempCByIndex(0);
        return String(temperatureC);
    }
    else
    {
        return String(random(10, 100));
    }
}