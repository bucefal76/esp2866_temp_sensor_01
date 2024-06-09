#ifndef SENSOR_DATA_SOURCE_IF
#define SENSOR_DATA_SOURCE_IF

#include <Arduino.h>

class SensorDataSourceIf
{
public:
    virtual size_t getNumberOfSources() const = 0;

    virtual String getStrValueOfTheSource(const uint8_t dataSourceId) const = 0;
};

#endif