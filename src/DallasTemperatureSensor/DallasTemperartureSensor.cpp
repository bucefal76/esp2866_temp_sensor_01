#include <OneWire.h>
#include <DallasTemperature.h>

#include "DallasTemperatureSensor\DallasTemperartureSensor.hpp"
#include "ModuleConfig.hpp"
#include "SerialPrintAssert.hpp"

#define TEMPERATURE_PRECISION 9

DallasTemperatureSensor::DallasTemperatureSensor()
    : m_pOneWire(nullptr), m_pDallasTemperature(nullptr)
{
    m_pOneWire = new OneWire(SENSOR_ONE_WIRE_INPUT);
    RUNTIME_PTR_CHECK(m_pOneWire);

    m_pDallasTemperature = new DallasTemperature(m_pOneWire);
    RUNTIME_PTR_CHECK(m_pDallasTemperature);
}

DallasTemperatureSensor::~DallasTemperatureSensor()
{
    if (m_pDallasTemperature != nullptr)
    {
        delete m_pDallasTemperature;
    }

    if (m_pOneWire != nullptr)
    {
        delete m_pOneWire;
    }
}

bool DallasTemperatureSensor::initialize()
{
    RUNTIME_PTR_CHECK(m_pDallasTemperature);

    m_pDallasTemperature->begin();

    if (m_pDallasTemperature->getDS18Count() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t DallasTemperatureSensor::getNumberOfSensors() const
{
    RUNTIME_PTR_CHECK(m_pDallasTemperature);

    return m_pDallasTemperature->getDS18Count();
}

String DallasTemperatureSensor::getStrValueOfTheSensor(const uint8_t dataSourceId) const
{
    RUNTIME_PTR_CHECK(m_pDallasTemperature);

    m_pDallasTemperature->requestTemperatures();
    float temperatureC = m_pDallasTemperature->getTempCByIndex(dataSourceId);
    return String(temperatureC);
}