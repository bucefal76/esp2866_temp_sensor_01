#include <Arduino.h>
#include "Application.hpp"

Application applicationTemperatureSensor;

void setup()
{
  applicationTemperatureSensor.initialize();
}

void loop()
{
  applicationTemperatureSensor.pushData();
}
