#include "Application.hpp"
#include "DataSourceIf.hpp"
#include "DallasTemperatureSensor\DallasTemperatureDataSource.hpp"

#define SERVER_PORT 80U

#define LED_ON LOW
#define LED_OFF HIGH

#ifdef POWER_SUPPLY_DIAGNOSTICS
ADC_MODE(ADC_VCC);
#endif

Application::Application()
    : m_ServerIpAddress(SERVER_IP_ADDRESS),
      m_pDataSource(nullptr)
{
}

void Application::initialize(DataSourceIf *dataSource)
{
#ifdef APPLICATION_USE_LED_FOR_ACTIVITY
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LED_ON);
#endif

    m_pDataSource = dataSource;

#ifdef USE_SERIAL
    Serial.begin(9600);
    Serial.println(F(APPLICATION_NAME));

    Serial.println(F("Initializing temperature sensors..."));
#endif
    while (m_pDataSource->initializeDataSource() != true)
    {
#ifdef USE_SERIAL
        Serial.println(F("Initializing temperature sensors..."));
#endif
        delay(APPLICATION_DATA_PUSH_TIME_INTERVAL);
    }

#ifdef USE_SERIAL
    Serial.println(F("Temperature sensors initalized!"));
    Serial.print(F("Number of active temperature sensors is: "));
    Serial.println(DallasTemperatureDataSource::getNumberOfSensors());

    // WiFI initialization
    Serial.println(F("Initializing WiFi connection..."));
#endif

    if (initializeWiFi())
    {
#ifdef USE_SERIAL
        Serial.println(F("The WiFi connection established!"));
#endif
    }

#ifdef APPLICATION_USE_LED_FOR_ACTIVITY
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LED_OFF);
#endif
}

void Application::processingLoop()
{
#ifdef APPLICATION_USE_LED_FOR_ACTIVITY
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LED_ON);
#endif

    pushData();

#ifdef APPLICATION_USE_LED_FOR_ACTIVITY
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LED_OFF);
#endif

#ifdef APPLICATION_USE_DEEP_SLEEP
#ifdef USE_SERIAL
    Serial.println(F("Going to the deep sleep..."));
#endif
    ESP.deepSleep(APPLICATION_DEEP_SLEEP_TIME);
#ifdef USE_SERIAL
    Serial.println(F("ERROR: Shall never get here!"));
#endif
#else
    delay(APPLICATION_DATA_PUSH_TIME_INTERVAL);
#endif
}

void Application::pushData()
{
    if (nullptr != m_pDataSource)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            // Connecting to the server
#ifdef USE_SERIAL
            Serial.println(F("Connecting to the server..."));
#endif

            if (m_WiFiClient.connect(m_ServerIpAddress, SERVER_PORT))
            {
#ifdef USE_SERIAL
                Serial.println(F("Server connection is opened with success!"));
#endif

                // Create a URL for the request, similar to this:
                // https://api.asksensors.com/write/apiKeyIn?module1=value1&module2=value2&module3=value3&module6=value6

                String url = "";
                url += SERVER_HOST_NAME;
                url += "/write/";
                url += SERVER_API_KEY;
                url += "?";

                url += m_pDataSource->getDataString();

#ifdef USE_SERIAL
                Serial.print(F("[HTTP] Requesting URL: "));
                Serial.println(url);
#endif

                m_HttpClient.begin(m_WiFiClient, url); // HTTP
#ifdef USE_SERIAL
                Serial.println(F("Request sent to ASKSENSORS"));

                Serial.print(F("[HTTP] GET...\n"));
#endif
                // start connection and send HTTP header
                int httpCode = m_HttpClient.GET();

                // httpCode will be negative on error
                if (httpCode > 0)
                {
                    // HTTP header has been send and Server response header has been handled
#ifdef USE_SERIAL
                    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
#endif

                    // file found at server
                    if (httpCode == HTTP_CODE_OK)
                    {
                        String payload = m_HttpClient.getString();
#ifdef USE_SERIAL
                        Serial.print(F("[HTTP] Payload is:"));
                        Serial.println(payload);
#endif
                    }
                }
                else
                {
#ifdef USE_SERIAL
                    Serial.printf("[HTTP] GET... failed, error: %s\n", m_HttpClient.errorToString(httpCode).c_str());
#endif
                }

                m_HttpClient.end();

                m_WiFiClient.stop();
#ifdef USE_SERIAL
                Serial.println(F("[HTTP] SUCCESS: data are send!"));
#endif
            }
            else
            {
#ifdef USE_SERIAL
                Serial.println(F("ERROR: Cannot connect to the server, will try again in a minute!"));
#endif
            }
        }
        else
        {
#ifdef USE_SERIAL
            Serial.println(F("ERROR: The WiFi connection is not established, reset device to try again!"));
#endif
        }
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
#ifdef USE_SERIAL
            Serial.print(F("ERROR: Failed WiFI connection try #:"));
            Serial.println(tryNo);
#endif

            delay(2500);
            tryNo++;

            if (tryNo > 3)
            {
#ifdef USE_SERIAL
                Serial.print(F("Resetting WiFI  settings now!"));
#endif
                m_WiFiManager.resetSettings();
                tryNo = 0;
            }
        }
    }

    return result;
}