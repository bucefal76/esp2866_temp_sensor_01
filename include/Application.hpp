#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <Arduino.h>
#include <WiFiManager.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

#include "ModuleConfig.hpp"

class SensorDataSourceIf;

class Application
{
public:
    Application();
    /// @brief Initalized application and sensor.
    /// @param sensorsDataSource Pointer to the sensors data source object.
    void initialize(SensorDataSourceIf *sensorsDataSource);
    /// @brief Do processing. Call it in the main loop.
    void processingLoop();

private:
    bool initializeWiFi();
    void pushData();
    void diagnosePowerSupply();

    IPAddress m_ServerIpAddress;
    SensorDataSourceIf *m_pDataSource;

    WiFiManager m_WiFiManager;
    WiFiClient m_WiFiClient;
    HTTPClient m_HttpClient;
};

#endif