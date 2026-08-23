#include "ota.h"

#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>

#include "config.h"


void otaInit()
{
    ArduinoOTA.setHostname(HOSTNAME);


    ArduinoOTA.onStart([]()
    {
        Serial.println("OTA START");
    });


    ArduinoOTA.onEnd([]()
    {
        Serial.println("\nOTA END");
    });


    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
    {
        Serial.printf(
            "OTA %u%%\n",
            (progress / (total / 100))
        );
    });


    ArduinoOTA.onError([](ota_error_t error)
    {
        Serial.printf(
            "OTA ERROR %u\n",
            error
        );
    });


    ArduinoOTA.begin();


    Serial.println("OTA READY");
}



void otaLoop()
{
    ArduinoOTA.handle();
}