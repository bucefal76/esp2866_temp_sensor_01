#ifndef SENSOR_DATA_SOURCE_IF
#define SENSOR_DATA_SOURCE_IF

#include <Arduino.h>

class SensorDataSourceIf
{
public:
    virtual bool initialize() = 0;

    virtual size_t getNumberOfSensors() const = 0;

    virtual String getStrValueOfTheSensor(const uint8_t sensorId) const = 0;
};

#endif