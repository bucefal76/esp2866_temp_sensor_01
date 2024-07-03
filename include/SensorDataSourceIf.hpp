#ifndef SENSOR_DATA_SOURCE_IF
#define SENSOR_DATA_SOURCE_IF

#include <Arduino.h>

class SensorDataSourceIf
{
public:
    /// @brief  Do some preparation on the sensor.
    /// @return True if initialization succeeded.
    virtual bool initialize() = 0;
    /// @brief Returns number os temperature sensors.
    virtual size_t getNumberOfSensors() const = 0;
    /// @brief  Returns temperate in Celsius.
    /// @param sensorId Id of the sensor we would like to have data read.
    /// @return String that represents float value.
    virtual String getStrValueOfTheSensor(const uint8_t sensorId) const = 0;
};

#endif