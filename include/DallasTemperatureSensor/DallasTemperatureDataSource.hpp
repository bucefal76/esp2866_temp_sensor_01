#ifndef DALLAS_TEMPERATURE_DATA_SOURCE_HPP
#define DALLAS_TEMPERATURE_DATA_SOURCE_HPP

#include "DataSourceIf.hpp"

class OneWire;
class DallasTemperature;

class DallasTemperatureDataSource : public DataSourceIf
{
public:
    DallasTemperatureDataSource();
    ~DallasTemperatureDataSource();

    /// @brief See DataSourceIf
    virtual String getDataString() override;
    /// @brief See DataSourceIf
    virtual bool initializeDataSource() override;

    /// @brief Returns number of the hardware temperature sensors.
    static size_t getNumberOfSensors();

private:
    uint8_t m_dataSourceId;

    static OneWire *m_pOneWire;
    static DallasTemperature *m_pDallasTemperature;
    static uint8_t m_referenceCount;
    static bool m_initalizedWitchSuccess;
};

#endif