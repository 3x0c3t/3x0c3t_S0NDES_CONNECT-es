#include "leds.h"
#include "settings.h"
#include "bootscreen.h"
#include <Arduino.h>

void ledsInit()
{
    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    ledsOff();
}

void ledsOff()
{
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);

    bootLedStatus(true);
}

void ledBlue()
{
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, HIGH);
}

void ledGreen()
{
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, LOW);
}

void ledRed()
{
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
}

void ledOrange()
{
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, LOW);
}

void ledsTest()
{
    ledBlue();
    delay(300);

    ledGreen();
    delay(300);

    ledRed();
    delay(300);

    ledsOff();
}

void ledsRainbow()
{
    ledRed();
    delay(200);

    ledGreen();
    delay(200);

    ledBlue();
    delay(200);

    ledsOff();
}

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

void ledsOrangeFade()
{
    for (int brightness = 0; brightness <= 255; brightness += 5)
    {
        analogWrite(LED_RED, brightness);
        analogWrite(LED_GREEN, brightness / 2);
        digitalWrite(LED_BLUE, LOW);

        delay(20);
    }

    for (int brightness = 255; brightness >= 0; brightness -= 5)
    {
        analogWrite(LED_RED, brightness);
        analogWrite(LED_GREEN, brightness / 2);
        digitalWrite(LED_BLUE, LOW);

        delay(20);
    }

    ledsOff();
}