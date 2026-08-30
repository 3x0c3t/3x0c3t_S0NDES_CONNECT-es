#include "ota.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

#include "config.h"
#include "debug.h"

// === OTA INIT ===

void otaInit()
{
    ArduinoOTA.setHostname(
        HOSTNAME
    );

    ArduinoOTA.onStart(
        []()
        {
            debugOtaStart();
        }
    );

    ArduinoOTA.onEnd(
        []()
        {
            debugOtaEnd();
        }
    );

    ArduinoOTA.onProgress(
        [](unsigned int progress, unsigned int total)
        {
            debugOtaProgress(
                progress,
                total
            );
        }
    );

    ArduinoOTA.onError(
        [](ota_error_t error)
        {
            debugOtaError(
                error
            );
        }
    );

    ArduinoOTA.begin();

    debugOtaReady();
}

// === OTA LOOP ===

void otaLoop()
{
    ArduinoOTA.handle();
}