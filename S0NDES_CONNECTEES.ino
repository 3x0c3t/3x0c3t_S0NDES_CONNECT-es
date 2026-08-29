#include <Arduino.h>

#include "config.h"
#include "settings.h"

#include "leds.h"
#include "buzzer.h"
#include "oled.h"
#include "splashScreen.h"
#include "bootscreen.h"
#include "wifi.h"
#include "ota.h"
#include "temperature.h"
#include "webserver.h"


// === SETUP
void setup()
{
    // === SERIAL
    Serial.begin(
        SERIAL_BAUDRATE
    );

    delay(500);


    // === OLED
    oledInit();


    // === START
    Serial.println();
    Serial.println(
        "=============================="
    );

    Serial.println(
        HOSTNAME
    );

    Serial.println(
        "DEMARRAGE"
    );

    Serial.println(
        "=============================="
    );


    // === LEDS
    ledsInit();

    ledsTest();


    // === BUZZER
    buzzerInit();


    // === SPLASH SCREEN
    splashScreen();


    // === BOOT SCREEN
    bootScreen();


    // === BUZZER STARTUP
    startupMelody();


    // === WIFI
    wifiInit();


    // === OTA
    otaInit();


    // === TEMPERATURES
    temperatureInit();


    // === WEBSERVER
    webserverInit();


    // === SETUP - END
    Serial.println();
    Serial.println(
        "=== ! SYSTEME PRET ! ==="
    );
}


// === LOOP
void loop()
{
    // === OTA
    otaLoop();


    // === WEBSERVER
    webserverLoop();


    // === TEMPERATURES
    readTemperatures();
}