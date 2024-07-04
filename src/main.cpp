#include <Arduino.h>
#include "Application.hpp"
#include "DallasTemperatureSensor\DallasTemperartureSensor.hpp"

Application applicationTemperatureSensor;
DallasTemperatureSensor temperatureDataSource;

void setup()
{
  applicationTemperatureSensor.initialize(&temperatureDataSource);
}

void loop()
{
  applicationTemperatureSensor.processingLoop();
}
