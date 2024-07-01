#ifndef TEMPERATURE_DATA_SOURCE_HPP
#define TEMPERATURE_DATA_SOURCE_HPP

#include "SensorDataSourceIf.hpp"

class TemperatureDataSource : public SensorDataSourceIf
{
public:
    virtual bool initialize();

    virtual size_t getNumberOfSources() const;

    virtual String getStrValueOfTheSource(const uint8_t dataSourceId) const;
};

#endif