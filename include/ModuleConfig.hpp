#ifndef MODULE_CONFIG_HPP
#define MODULE_CONFIG_HPP

#define USE_SERIAL

#define APPLICATION_NAME "TemperatureSensor A01"
#define APPLICATION_NUMBER_OF_SENSORS 4
#define APPLICATION_DATA_PUSH_TIME_INTERVAL 5000
//#define APPLICATION_USE_DEEP_SLEEP
#ifdef APPLICATION_USE_DEEP_SLEEP
#define APPLICATION_DEEP_SLEEP_TIME 300e6
#endif
#define APPLICATION_USE_LED_FOR_ACTIVITY

#define SERVER_IP_ADDRESS 52, 14, 123, 233
#define SERVER_HOST_NAME "http://api.asksensors.com"
#define SERVER_API_KEY "9sF8ibj8KSB8Qvdh3XQlp2dnd1ufutRj"

#define POWER_SUPPLY_DIAGNOSTICS

/// Deep sleep wake up line is D0
#define WIFI_SETTINGS_CLEAR_INPUT_LINE D1
#define SENSOR_ONE_WIRE_INPUT_LINE D2

#define VOLTAGE_LEVEL_WARNING 2650 // Corresponds to 3.1V
#define VOLTAGE_LEVEL_ERROR 2550   // Corresponds to the voltage above 3V, minimum for the selected batteryB

#endif