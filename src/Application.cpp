#include "Application.hpp"

#define SERVER_PORT 80U

Application::Application()
    : m_ServerIpAddress(SERVER_IP_ADDRESS)
{
}

void Application::initialize()
{
    Serial.begin(9600);
    Serial.println(F(APPLICATION_NAME));

    // WiFI initialization
    Serial.println(F("Initializing WiFi connection..."));

    if (initializeWiFi())
    {
        Serial.println(F("The WiFi connection established!"));
    }
}

void Application::pushData()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        // Connecting to the server
        Serial.println(F("Connecting to the server..."));

        if (m_WiFiClient.connect(m_ServerIpAddress, SERVER_PORT))
        {
            Serial.println(F("Server connection is opened with success!"));

            // Create a URL for the request
            String url = "";
            url += SERVER_HOST_NAME;
            url += "/write/";
            url += SERVER_API_KEY;
            url += "?module1=";
            url += random(10, 100);

            Serial.print("Requesting URL: ");
            Serial.println(url);

            m_HttpClient.begin(m_WiFiClient, url); // HTTP

            Serial.println("Request sent to ASKSENSORS");

            Serial.print("[HTTP] GET...\n");
            // start connection and send HTTP header
            int httpCode = m_HttpClient.GET();

            // httpCode will be negative on error
            if (httpCode > 0)
            {
                // HTTP header has been send and Server response header has been handled
                Serial.printf("[HTTP] GET... code: %d\n", httpCode);

                // file found at server
                if (httpCode == HTTP_CODE_OK)
                {
                    String payload = m_HttpClient.getString();
                    Serial.println(payload);
                }
            }
            else
            {
                Serial.printf("[HTTP] GET... failed, error: %s\n", m_HttpClient.errorToString(httpCode).c_str());
            }

            m_HttpClient.end();

            Serial.println("[HTTP] SUCCESS: data are send!");

            delay(APPLICATION_DATA_PUSH_TIME_INTERVAL);
        }
        else
        {
            Serial.println(F("ERROR: Cannot connect to the server, will try again in a minute!"));
        }
    }
    else
    {
        Serial.println(F("ERROR: The WiFi connection is not established, reset device to try again!"));
    }
}

bool Application::initializeWiFi()
{
    bool result = false;

    uint8_t tryNo = 0;

    while (false == result)
    {
        result = m_WiFiManager.autoConnect(APPLICATION_NAME);

        if (result == false)
        {
            Serial.print(F("ERROR: Failed WiFI connection try #:"));
            Serial.println(tryNo);

            delay(2500);
            tryNo++;

            if (tryNo > 3)
            {
                Serial.print(F("Resetting WiFI  settings now!"));
                m_WiFiManager.resetSettings();
                tryNo = 0;
            }
        }
    }

    return result;
}