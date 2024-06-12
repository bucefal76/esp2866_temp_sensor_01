#include <Arduino.h>
#include "Application.hpp"
#include "TemperatureDataSource.hpp"

Application applicationTemperatureSensor;
TemperatureDataSource temperatureDataSource;

void setup()
{
  applicationTemperatureSensor.initialize(&temperatureDataSource);
}

void loop()
{
  applicationTemperatureSensor.processingLoop();
}
