#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <Arduino.h>
#include <WiFiManager.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

#include "ModuleConfig.hpp"

class Application
{
public:
    Application();

    void initialize();

    void pushData();

private:
    bool initializeWiFi();

    IPAddress m_ServerIpAddress;

    WiFiManager m_WiFiManager;
    WiFiClient m_WiFiClient;
    HTTPClient m_HttpClient;
};

#endif