#include <Arduino.h>
#include "Application.hpp"
#include "CompositeDataSource.hpp"
#include "DallasTemperatureSensor/DallasTemperatureDataSource.hpp"
#include "ModuleConfig.hpp"

Application applicationTemperatureSensor;
CompositeDataSource compositeDataSource;

void setup()
{
  // Create sensors and put them into the temperature composite:
  for (uint8_t i = 0; i < APPLICATION_NUMBER_OF_SENSORS; i++)
  {
    DallasTemperatureDataSource *pDataSource = new DallasTemperatureDataSource();
    compositeDataSource.addDataSource(pDataSource);
  }

  applicationTemperatureSensor.initialize(&compositeDataSource);
}

void loop()
{
  applicationTemperatureSensor.processingLoop();
}
