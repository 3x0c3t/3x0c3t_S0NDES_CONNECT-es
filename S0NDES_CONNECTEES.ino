#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "config.h"
#include "oled.h"
#include "splashScreen.h"
#include "bootscreen.h"
#include "leds.h"
#include "buzzer.h"
#include "wifi.h"
#include "temperature.h"
#include "webserver.h"
#include "debug.h"

// === SETUP ===

void setup()
{
    // === SERIAL ===

    Serial.begin(
        SERIAL_BAUDRATE
    );

    delay(100);

    debugStartup();

    // === OLED ===

    oledInit();

    oled.clearBuffer();
    oled.sendBuffer();

    // === SPLASH SCREEN ===

    splashScreen();

    // === LEDS ===

    ledsInit();
    ledsTest();

    // === BUZZER ===

    buzzerInit();

    // === TEMPERATURES ===

    temperatureInit();

    // === WIFI ===

    wifiInit();

    // === SERVEUR WEB ===

    if (
        WiFi.status() ==
        WL_CONNECTED
    )
    {
        webserverInit();
    }
    else
    {
        debugWebserverNotStarted();
    }

    // === AFFICHAGE TEMPERATURES ===

    temperatureScreen();

    // === SYSTEME PRET ===

    debugSystemReady();
}

// === LOOP ===

void loop()
{
    // === SERVEUR HTTP ===

    webserverLoop();

    // === TEMPERATURES ===

    readTemperatures();

    // === WIFI ===

    if (
        WiFi.status() !=
        WL_CONNECTED
    )
    {
        /*
         * Pas de reconnexion automatique ici pour le moment.
         */
    }

    // === PETITE PAUSE ===

    yield();
}