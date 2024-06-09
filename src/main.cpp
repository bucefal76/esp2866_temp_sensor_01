#include <Arduino.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

WiFiManager wm;
WiFiClient client;
HTTPClient http;

String host = "http://api.asksensors.com"; // ASKSENSORS API host name
IPAddress server(52,14,123,233);

const char *apiKeyIn = "9sF8ibj8KSB8Qvdh3XQlp2dnd1ufutRj"; // API KEY IN
const unsigned int writeInterval = 25000;                  // write interval (in ms)

void setup()
{
  // WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  // it is a good practice to make sure your code sets wifi mode how you want it.

  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("Starting..."));

  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
  res = wm.autoConnect("AutoConnectAP"); // anonymous ap

  if (!res)
  {
    Serial.println("Failed to connect");
    // ESP.restart();
  }
  else
  {
    // if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
  }
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {

    Serial.println("WiFI Status connected!");

    if (client.connect(server, 80))
    {
      Serial.print("[TCP] Port 80 opened ...\n");

      Serial.print("[HTTP] begin...\n");

      // Create a URL for the request
      String url = "";
      url += host;
      url += "/write/";
      url += apiKeyIn;
      url += "?module1=";
      url += random(10, 100);

      Serial.print("********** requesting URL: ");
      Serial.println(url);

      http.begin(client, url); // HTTP

      Serial.println("> Request sent to ASKSENSORS");

      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0)
      {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK)
        {
          String payload = http.getString();
          Serial.println(payload);
        }
      }
      else
      {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();

      Serial.println("********** End ");
      Serial.println("*****************************************************");
    }
  }

  delay(writeInterval); // wait for writeInterval
}
