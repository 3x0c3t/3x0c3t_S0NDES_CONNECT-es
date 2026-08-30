#include "leds.h"
#include <Arduino.h>
#include "settings.h"
#include "debug.h"


// ============================================================
// INITIALISATION
// ============================================================

void ledsInit()
{
    debugLedsInitStart();

    pinMode(
        LED_BLUE,
        OUTPUT
    );

    pinMode(
        LED_GREEN,
        OUTPUT
    );

    pinMode(
        LED_RED,
        OUTPUT
    );

    ledsOff();

    debugLedBluePin(
        LED_BLUE,
        digitalRead(LED_BLUE)
    );

    debugLedGreenPin(
        LED_GREEN,
        digitalRead(LED_GREEN)
    );

    debugLedRedPin(
        LED_RED,
        digitalRead(LED_RED)
    );

    debugLedsInitEnd();
}


// ============================================================
// LEDS OFF
// ============================================================

void ledsOff()
{
    digitalWrite(
        LED_BLUE,
        LOW
    );

    digitalWrite(
        LED_GREEN,
        LOW
    );

    digitalWrite(
        LED_RED,
        LOW
    );

    debugLedsOff();
}


// ============================================================
// LED BLEUE
// ============================================================

void ledBlue()
{
    debugLedBlue();

    digitalWrite(
        LED_BLUE,
        HIGH
    );

    debugLedBluePin(
        LED_BLUE,
        digitalRead(LED_BLUE)
    );
}


// ============================================================
// LED VERTE
// ============================================================

void ledGreen()
{
    debugLedGreen();

    digitalWrite(
        LED_GREEN,
        HIGH
    );

    debugLedGreenPin(
        LED_GREEN,
        digitalRead(LED_GREEN)
    );
}


// ============================================================
// LED ROUGE
// ============================================================

void ledRed()
{
    debugLedRed();

    digitalWrite(
        LED_RED,
        HIGH
    );

    debugLedRedPin(
        LED_RED,
        digitalRead(LED_RED)
    );
}


// ============================================================
// CLIGNOTEMENT VERT 3 FOIS
// ============================================================

void ledsGreenBlink3()
{
    for (
        uint8_t i = 0;
        i < 3;
        i++
    )
    {
        digitalWrite(
            LED_GREEN,
            HIGH
        );

        delay(200);

        digitalWrite(
            LED_GREEN,
            LOW
        );

        delay(200);
    }
}


// ============================================================
// CLIGNOTEMENT ROUGE 3 FOIS
// ============================================================

void ledsRedBlink3()
{
    for (
        uint8_t i = 0;
        i < 3;
        i++
    )
    {
        digitalWrite(
            LED_RED,
            HIGH
        );

        delay(200);

        digitalWrite(
            LED_RED,
            LOW
        );

        delay(200);
    }
}


// ============================================================
// TEST LEDS
// ============================================================

void ledsTest()
{
    debugLedsTestStart();

    ledsOff();

    ledRed();

    delay(1000);

    ledsOff();

    ledGreen();

    delay(1000);

    ledsOff();

    ledBlue();

    delay(1000);

    ledsOff();

    debugLedsTestEnd();
}