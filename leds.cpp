#include "leds.h"

#include <Arduino.h>

#include "settings.h"
#include "bootscreen.h"


// ============================================================
// INITIALISATION
// ============================================================

void ledsInit()
{
    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);

    bootLedStatus(true);
}


// ============================================================
// TOUTES LES LEDS OFF
// ============================================================

void ledsOff()
{
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);

    Serial.println("LED OFF");

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

    Serial.print("GPIO14 immédiatement = ");
    Serial.println(digitalRead(LED_BLUE));

    delay(2000);

    Serial.print("GPIO14 après 2 secondes = ");
    Serial.println(digitalRead(LED_BLUE));
}


// ============================================================
// VERT
// ============================================================

void ledGreen()
{
    Serial.println(">>> ledGreen()");

    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_RED, LOW);

    digitalWrite(LED_GREEN, HIGH);

    Serial.print("GPIO12 = ");
    Serial.println(digitalRead(LED_GREEN));
}


// ============================================================
// ROUGE
// ============================================================

void ledRed()
{
    Serial.println(">>> ledRed()");

    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);

    digitalWrite(LED_RED, HIGH);

    Serial.print("GPIO13 = ");
    Serial.println(digitalRead(LED_RED));
}


// ============================================================
// ORANGE
// ============================================================

void ledOrange()
{
    Serial.println(">>> ledOrange()");

    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    digitalWrite(LED_BLUE, LOW);

    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, HIGH);

    Serial.print("GPIO13 = ");
    Serial.println(digitalRead(LED_RED));

    Serial.print("GPIO12 = ");
    Serial.println(digitalRead(LED_GREEN));
}


// ============================================================
// TEST LEDS
// ============================================================

void ledsTest()
{
    Serial.println();
    Serial.println("==============================");
    Serial.println("TEST LEDS");
    Serial.println("==============================");

    ledBlue();
    delay(500);

    ledsOff();
    delay(300);

    ledGreen();
    delay(500);

    ledsOff();
    delay(300);

    ledRed();
    delay(500);

    ledsOff();
    delay(300);

    ledOrange();
    delay(500);

    ledsOff();

    Serial.println("==============================");
    Serial.println("TEST LEDS TERMINE");
    Serial.println("==============================");
}


// ============================================================
// ARC-EN-CIEL
// ============================================================

void ledsRainbow()
{
    ledRed();
    delay(500);

    ledGreen();
    delay(500);

    ledBlue();
    delay(500);

    ledsOff();
}


// ============================================================
// CLIGNOTEMENT VERT
// ============================================================

void ledsGreenBlink3()
{
    for (int i = 0; i < 3; i++)
    {
        ledGreen();
        delay(200);

        ledsOff();
        delay(200);
    }
}


// ============================================================
// CLIGNOTEMENT ROUGE
// ============================================================

void ledsRedBlink3()
{
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
    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    digitalWrite(LED_BLUE, LOW);

    for (int brightness = 0; brightness <= 255; brightness += 5)
    {
        analogWrite(LED_RED, brightness);
        analogWrite(LED_GREEN, brightness / 2);

        delay(20);
    }

    for (int brightness = 255; brightness >= 0; brightness -= 5)
    {
        analogWrite(LED_RED, brightness);
        analogWrite(LED_GREEN, brightness / 2);

        delay(20);
    }

    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
}