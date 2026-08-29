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
        LED_GREEN,
        LOW
    );

    digitalWrite(
        LED_RED,
        LOW
    );

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
        LED_BLUE,
        LOW
    );

    digitalWrite(
        LED_RED,
        LOW
    );

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
        LED_BLUE,
        LOW
    );

    digitalWrite(
        LED_GREEN,
        LOW
    );

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
// TEST LEDS
// ============================================================

void ledsTest()
{
    debugLedsTestStart();

    ledBlue();
    delay(1000);

    ledGreen();
    delay(1000);

    ledRed();
    delay(1000);

    ledsOff();

    debugLedsTestEnd();
}


// ============================================================
// ARC-EN-CIEL
// ============================================================

void ledsRainbow()
{
    debugLedsRainbow();

    ledRed();
    delay(500);

    ledGreen();
    delay(500);

    ledBlue();
    delay(500);

    ledsOff();
}


// ============================================================
// VERT : 3 CLIGNOTEMENTS
// ============================================================

void ledsGreenBlink3()
{
    debugLedGreenBlinkStart();

    for (
        int i = 0;
        i < 3;
        i++
    )
    {
        ledGreen();

        delay(250);

        ledsOff();

        delay(250);
    }
}


// ============================================================
// ROUGE : 3 CLIGNOTEMENTS
// ============================================================

void ledsRedBlink3()
{
    debugLedRedBlinkStart();

    for (
        int i = 0;
        i < 3;
        i++
    )
    {
        ledRed();

        delay(250);

        ledsOff();

        delay(250);
    }
}