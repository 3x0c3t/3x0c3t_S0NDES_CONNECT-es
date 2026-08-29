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
#include "webserver.h"
#include "temperature.h"

void setup()
{
    // === SERIAL MONITORING
    Serial.begin(SERIAL_BAUDRATE);

    delay(500);

    oledInit();

    Serial.println();
    Serial.println("==============================");
    Serial.println(HOSTNAME);
    Serial.println("DEMARRAGE");
    Serial.println("==============================");

    // === LEDS | INIT > TEST
    ledsInit();
    ledsTest();

    // BUZZER | INIT > TEST
    buzzerInit();

    // OLED | INIT > SPLASHSCREEN > BOOTSCREEN
    oledInit();
    splashScreen();
    bootScreen();

    // === BUZZER | TEST
    startupMelody();

    // === WIFI | INIT
    wifiInit();

    // === OTA | INIT
    otaInit();

    // === TEMPERATURES | INIT
    temperatureInit();

    // === WEBSERVER | INIT
    webserverInit();

    // === SETUP - END
    Serial.println();
    Serial.println("=== ! SYSTEME PRET ! ===");
}


void loop()
{
    // === OTA | LOOP
    otaLoop();

    // === WEBSERVER | LOOP
    webserverLoop();
}