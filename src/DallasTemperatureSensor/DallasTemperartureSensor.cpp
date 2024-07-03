#include <OneWire.h>
#include <DallasTemperature.h>

#include "DallasTemperatureSensor\DallasTemperartureSensor.hpp"
#include "ModuleConfig.hpp"

#define TEMPERATURE_PRECISION 9

OneWire oneWire(SENSOR_ONE_WIRE_INPUT);
DallasTemperature sensors(&oneWire);

bool DallasTemperatureSensor::initialize()
{
    sensors.begin();

    if (sensors.getDS18Count() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t DallasTemperatureSensor::getNumberOfSensors() const
{
    return sensors.getDS18Count();
}

String DallasTemperatureSensor::getStrValueOfTheSensor(const uint8_t dataSourceId) const
{
    sensors.requestTemperatures();
    float temperatureC = sensors.getTempCByIndex(dataSourceId);
    return String(temperatureC);
}