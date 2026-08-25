#include <Arduino.h>

#include "ota.h"
#include "config.h"
#include "leds.h"
#include "buzzer.h"
#include "oled.h"
#include "splashScreen.h"
#include "bootscreen.h"
#include "wifi.h"
#include "webserver.h"
#include "temperature.h"

void setup()
{
    Serial.begin(SERIAL_BAUDRATE);

    ledsInit();
    buzzerInit();

    oledInit();
    splashScreen();
    bootScreen();

    ledsTest();
    startupMelody();

    wifiInit();
    otaInit();

    temperatureInit();
    webserverInit();
}

void loop()
{
    // --------------------------------------------------------
    // OTA
    // --------------------------------------------------------

    otaLoop();


    // --------------------------------------------------------
    // SERVEUR WEB
    // --------------------------------------------------------

    webserverLoop();


    // --------------------------------------------------------
    // TEMPÉRATURES
    // --------------------------------------------------------

    static unsigned long temperatureTimer = 0;


    if (millis() - temperatureTimer >= 5000)
    {
        temperatureTimer = millis();

        readTemperatures();

        temperatureScreen();
    }


    // --------------------------------------------------------
    // Laisser respirer l'ESP8266
    // --------------------------------------------------------

    yield();
}