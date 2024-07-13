#ifndef POWER_VOLTAGE_DATA_SOURCE_HPP
#define POWER_VOLTAGE_DATA_SOURCE_HPP

#include "DataSourceIf.hpp"

class PowerVoltageDataSource : public DataSourceIf
{
public:
    virtual bool initializeDataSource();
    virtual String getDataString();
};

#endif