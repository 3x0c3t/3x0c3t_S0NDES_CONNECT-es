#include "leds.h"
#include "settings.h"
#include "bootscreen.h"

#include <Arduino.h>


// ============================================================
// INITIALISATION
// ============================================================

void ledsInit()
{
    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    Serial.println("LED : initialisation");

    ledsOff();
}


// ============================================================
// TOUTES LES LEDS OFF
// ============================================================

void ledsOff()
{
    Serial.println(">>> ledsOff()");

    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);

    Serial.print("GPIO BLUE = ");
    Serial.println(digitalRead(LED_BLUE));

    bootLedStatus(true);
}


// ============================================================
// BLEU
// ============================================================

void ledBlue()
{
    Serial.println(">>> ledBlue()");

    pinMode(LED_BLUE, OUTPUT);

    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);

    digitalWrite(LED_BLUE, HIGH);

    Serial.print("GPIO14 = ");
    Serial.println(digitalRead(LED_BLUE));

    while (true)
    {
        digitalWrite(LED_BLUE, HIGH);

        Serial.print(
            "GPIO14 maintien HIGH = "
        );

        Serial.println(
            digitalRead(LED_BLUE)
        );

        delay(1000);

        yield();
    }
}


// ============================================================
// VERT
// ============================================================

void ledGreen()
{
    Serial.println(">>> ledGreen()");

    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, LOW);

    Serial.print("GPIO GREEN = ");
    Serial.println(digitalRead(LED_GREEN));
}


// ============================================================
// ROUGE
// ============================================================

void ledRed()
{
    Serial.println(">>> ledRed()");

    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);

    Serial.print("GPIO RED = ");
    Serial.println(digitalRead(LED_RED));
}


// ============================================================
// ORANGE
// ============================================================

void ledOrange()
{
    Serial.println(">>> ledOrange()");

    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, LOW);

    Serial.print("GPIO RED = ");
    Serial.println(digitalRead(LED_RED));

    Serial.print("GPIO GREEN = ");
    Serial.println(digitalRead(LED_GREEN));
}


// ============================================================
// TEST LEDS
// ============================================================

void ledsTest()
{
    Serial.println(">>> ledsTest()");

    ledBlue();
    delay(300);

    ledsOff();
    delay(100);

    ledGreen();
    delay(300);

    ledsOff();
    delay(100);

    ledRed();
    delay(300);

    ledsOff();
}


// ============================================================
// RAINBOW
// ============================================================

void ledsRainbow()
{
    Serial.println(">>> ledsRainbow()");

    ledRed();
    delay(200);

    ledGreen();
    delay(200);

    ledBlue();
    delay(200);

    ledsOff();
}


// ============================================================
// VERT CLIGNOTANT 3 FOIS
// ============================================================

void ledsGreenBlink3()
{
    Serial.println(">>> ledsGreenBlink3()");

    for (int i = 0; i < 3; i++)
    {
        ledGreen();
        delay(200);

        ledsOff();
        delay(200);
    }
}


// ============================================================
// ROUGE CLIGNOTANT 3 FOIS
// ============================================================

void ledsRedBlink3()
{
    Serial.println(">>> ledsRedBlink3()");

    for (int i = 0; i < 3; i++)
    {
        ledRed();
        delay(200);

        ledsOff();
        delay(200);
    }
}


// ============================================================
// ORANGE FADE
// ============================================================

void ledsOrangeFade()
{
    Serial.println(">>> ledsOrangeFade()");

    for (
        int brightness = 0;
        brightness <= 255;
        brightness += 5
    )
    {
        analogWrite(
            LED_RED,
            brightness
        );

        analogWrite(
            LED_GREEN,
            brightness / 2
        );

        digitalWrite(
            LED_BLUE,
            LOW
        );

        delay(20);
    }


    for (
        int brightness = 255;
        brightness >= 0;
        brightness -= 5
    )
    {
        analogWrite(
            LED_RED,
            brightness
        );

        analogWrite(
            LED_GREEN,
            brightness / 2
        );

        digitalWrite(
            LED_BLUE,
            LOW
        );

        delay(20);
    }

    ledsOff();
}