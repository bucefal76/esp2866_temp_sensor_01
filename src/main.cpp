#include <Arduino.h>
#include "Application.hpp"
#include "CompositeDataSource.hpp"
#include "DallasTemperatureSensor/DallasTemperatureDataSource.hpp"
#include "PowerVoltageDataSource/PowerVoltageDataSource.hpp"
#include "PowerVoltageDataSource/PowerVoltageThresholdDataSource.hpp"
#include "SerialPrintAssert.hpp"
#include "ModuleConfig.hpp"

Application applicationTemperatureSensor;

void setup()
{
  CompositeDataSource *pCompositeDataSource = new CompositeDataSource();
  RUNTIME_PTR_CHECK(pCompositeDataSource);

  // Create sensors and put them into the temperature composite:
  for (uint8_t i = 0; i < APPLICATION_NUMBER_OF_SENSORS; i++)
  {
    DallasTemperatureDataSource *pDataSource = new DallasTemperatureDataSource();
    RUNTIME_PTR_CHECK(pDataSource);
    pCompositeDataSource->addDataSource(pDataSource);
  }

#ifdef POWER_SUPPLY_DIAGNOSTICS
  PowerVoltageDataSource *pPowerVoltageDataSource = new PowerVoltageDataSource();
  RUNTIME_PTR_CHECK(pPowerVoltageDataSource);
  pCompositeDataSource->addDataSource(pPowerVoltageDataSource);

  PowerVoltageThresholdDataSource *pPowerVoltageThresholdDataSource = new PowerVoltageThresholdDataSource;
  RUNTIME_PTR_CHECK(pPowerVoltageThresholdDataSource);
  pCompositeDataSource->addDataSource(pPowerVoltageThresholdDataSource);
#endif

  applicationTemperatureSensor.initialize(pCompositeDataSource);
}

void loop()
{
  applicationTemperatureSensor.processingLoop();
}
