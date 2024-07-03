#ifndef DALLAS_TEMPERATURE_SENSOR_HPP
#define DALLAS_TEMPERATURE_SENSOR_HPP

#include "SensorDataSourceIf.hpp"

class DallasTemperatureSensor : public SensorDataSourceIf
{
public:
    virtual bool initialize();

    virtual size_t getNumberOfSensors() const;

    virtual String getStrValueOfTheSensor(const uint8_t dataSourceId) const;
};

#endif