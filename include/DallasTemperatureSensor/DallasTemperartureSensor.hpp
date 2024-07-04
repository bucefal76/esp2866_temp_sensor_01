#ifndef DALLAS_TEMPERATURE_SENSOR_HPP
#define DALLAS_TEMPERATURE_SENSOR_HPP

#include "SensorDataSourceIf.hpp"

class OneWire;
class DallasTemperature;

class DallasTemperatureSensor : public SensorDataSourceIf
{
public:
    DallasTemperatureSensor();
    ~DallasTemperatureSensor();
    /// @brief See SensorDataSourceIf.
    virtual bool initialize();
    /// @brief See SensorDataSourceIf.
    virtual size_t getNumberOfSensors() const;
    /// @brief See SensorDataSourceIf.
    virtual String getStrValueOfTheSensor(const uint8_t dataSourceId) const;

private:
    OneWire *m_pOneWire;
    DallasTemperature *m_pDallasTemperature;
};

#endif