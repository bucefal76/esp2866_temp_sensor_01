#include "Application.hpp"
#include "SensorDataSourceIf.hpp"

#define SERVER_PORT 80U

#define LED_ON LOW
#define LED_OFF HIGH

Application::Application()
    : m_ServerIpAddress(SERVER_IP_ADDRESS),
      m_pDataSource(nullptr)
{
}

void Application::initialize(SensorDataSourceIf *sensorsDataSource)
{
#ifdef APPLICATION_USE_LED_FOR_ACTIVITY
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LED_ON);
#endif

    m_pDataSource = sensorsDataSource;

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
    if (nullptr != m_pDataSource)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            // Connecting to the server
            Serial.println(F("Connecting to the server..."));

            if (m_WiFiClient.connect(m_ServerIpAddress, SERVER_PORT))
            {
                Serial.println(F("Server connection is opened with success!"));

                // Create a URL for the request, similar to this:
                // https://api.asksensors.com/write/apiKeyIn?module1=value1&module2=value2&module3=value3&module6=value6

                String url = "";
                url += SERVER_HOST_NAME;
                url += "/write/";
                url += SERVER_API_KEY;
                url += "?";

                for (uint8_t i = 0; i < m_pDataSource->getNumberOfSources(); i++)
                {
                    url += "module";
                    url += String(i + 1);
                    url += "=";
                    url += m_pDataSource->getStrValueOfTheSource(i);

                    if (i < m_pDataSource->getNumberOfSources() - 1)
                    {
                        url += "&";
                    }
                }

                Serial.print(F("[HTTP] Requesting URL: "));
                Serial.println(url);

                m_HttpClient.begin(m_WiFiClient, url); // HTTP

                Serial.println(F("Request sent to ASKSENSORS"));

                Serial.print(F("[HTTP] GET...\n"));
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
                        Serial.print(F("[HTTP] Payload is:"));
                        Serial.println(payload);
                    }
                }
                else
                {
                    Serial.printf("[HTTP] GET... failed, error: %s\n", m_HttpClient.errorToString(httpCode).c_str());
                }

                m_HttpClient.end();

                Serial.println(F("[HTTP] SUCCESS: data are send!"));
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

#ifdef APPLICATION_USE_LED_FOR_ACTIVITY
    digitalWrite(LED_BUILTIN, LED_OFF);
#endif

#ifdef APPLICATION_USE_DEEP_SLEEP
    Serial.println(F("Going to the deep sleep..."));
    ESP.deepSleep(APPLICATION_DEEP_SLEEP_TIME);
    Serial.println(F("ERROR: Shall never get here!"));
#endif

    delay(APPLICATION_DATA_PUSH_TIME_INTERVAL);
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