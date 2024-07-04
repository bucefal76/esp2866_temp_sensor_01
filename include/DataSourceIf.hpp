#ifndef DATA_SOURCE_IF_HPP
#define DATA_SOURCE_IF_HPP

#include <Arduino.h>

class DataSourceIf
{
public:
    /// @brief  Do some preparation on the sensor.
    /// @return True if initialization succeeded.
    virtual bool initializeDataSource() = 0;
    /// @brief  Returns temperate in Celsius.
    /// @param sensorId Id of the sensor we would like to have data read.
    /// @return String that represents float value.
    virtual String getDataString() = 0;
};

#endif