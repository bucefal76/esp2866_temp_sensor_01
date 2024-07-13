#ifndef POWER_VOLTAGE_THRESHOLD_DATA_SOURCE_HPP
#define POWER_VOLTAGE_THRESHOLD_DATA_SOURCE_HPP

#include "DataSourceIf.hpp"

class PowerVoltageThresholdDataSource : public DataSourceIf
{
public:
    virtual bool initializeDataSource();
    virtual String getDataString();
};

#endif