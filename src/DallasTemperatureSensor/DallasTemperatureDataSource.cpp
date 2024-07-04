#include <OneWire.h>
#include <DallasTemperature.h>

#include "DallasTemperatureSensor/DallasTemperatureDataSource.hpp"
#include "ModuleConfig.hpp"
#include "SerialPrintAssert.hpp"

OneWire *DallasTemperatureDataSource::m_pOneWire = nullptr;
DallasTemperature *DallasTemperatureDataSource::m_pDallasTemperature = nullptr;
uint8_t DallasTemperatureDataSource::m_referenceCount = 0U;
bool DallasTemperatureDataSource::m_initalizedWitchSuccess = false;

DallasTemperatureDataSource::DallasTemperatureDataSource()
{
    if (nullptr == m_pOneWire)
    {
        m_pOneWire = new OneWire(SENSOR_ONE_WIRE_INPUT);
    }
    RUNTIME_PTR_CHECK(m_pOneWire);

    if (nullptr == m_pDallasTemperature)
    {
        m_pDallasTemperature = new DallasTemperature(m_pOneWire);
    }
    RUNTIME_PTR_CHECK(m_pDallasTemperature);

    m_dataSourceId = m_referenceCount;

    m_referenceCount++;
}

bool DallasTemperatureDataSource::initializeDataSource()
{
    if (m_dataSourceId == 0U)
    {
        m_pDallasTemperature->begin();

        if (m_pDallasTemperature->getDS18Count() > 0)
        {
            m_initalizedWitchSuccess = true;
        }
        else
        {
            m_initalizedWitchSuccess = false;
        }
    }

    return m_initalizedWitchSuccess;
}

DallasTemperatureDataSource::~DallasTemperatureDataSource()
{
    m_referenceCount--;
}

size_t DallasTemperatureDataSource::getNumberOfSensors()
{
    RUNTIME_PTR_CHECK(m_pDallasTemperature);

    return m_pDallasTemperature->getDS18Count();
}

String DallasTemperatureDataSource::getDataString()
{
    RUNTIME_PTR_CHECK(m_pDallasTemperature);

    m_pDallasTemperature->requestTemperatures();
    float temperatureC = m_pDallasTemperature->getTempCByIndex(m_dataSourceId);
    return String(temperatureC);
}