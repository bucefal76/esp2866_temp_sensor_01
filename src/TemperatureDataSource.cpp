#include "TemperatureDataSource.hpp"
#include "ModuleConfig.hpp"

size_t TemperatureDataSource::getNumberOfSources() const
{
    return APPLICATION_NUMBER_OF_SENSORS;
}

String TemperatureDataSource::getStrValueOfTheSource(const uint8_t dataSourceId) const
{
    return String(random(10, 100));
}