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

// === SETUP ===

void setup()
{
    // === SERIAL ===
    Serial.begin(SERIAL_BAUDRATE);
    delay(500);

    // === OLED ===
    oledInit();

    // === NETTOYAGE ECRAN ===
    oled.clearBuffer();
    oled.sendBuffer();

    // === SPLASH SCREEN ===
    splashScreen();

    // === BOOT SCREEN ===
    bootScreen();

    // === LEDS ===
    ledsInit();
    ledsTest();

    // === BUZZER ===
    buzzerInit();

    // === BUZZER STARTUP ===
    startupMelody();

    // === WIFI ===
    wifiInit();

    // === OTA ===
    otaInit();

    // === TEMPERATURES ===
    temperatureInit();

    // === WEBSERVER ===
    webserverInit();

    // === FIN SETUP ===
    Serial.println();
    Serial.println("=== ! SYSTEME PRET ! ===");
}

// === LOOP ===

void loop()
{
    // === OTA ===
    otaLoop();

    // === WEBSERVER ===
    webserverLoop();

    // === TEMPERATURES ===
    readTemperatures();
}