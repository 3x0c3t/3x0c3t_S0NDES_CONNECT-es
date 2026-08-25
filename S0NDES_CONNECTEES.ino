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
    otaLoop();
    
    webserverLoop();

    static unsigned long timer;

    if (millis() - timer > 5000)
    {
        timer = millis();

        readTemperatures();
        temperatureScreen();
    }
}