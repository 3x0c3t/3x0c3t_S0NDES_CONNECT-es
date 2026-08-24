#include "leds.h"
#include "settings.h"
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
    analogWrite(LED_BLUE, 0);
    analogWrite(LED_GREEN, 0);
    analogWrite(LED_RED, 0);
}


void ledsTest()
{
    analogWrite(LED_BLUE, 255);
    delay(300);
    analogWrite(LED_BLUE, 0);

    analogWrite(LED_GREEN, 255);
    delay(300);
    analogWrite(LED_GREEN, 0);

    analogWrite(LED_RED, 255);
    delay(300);
    analogWrite(LED_RED, 0);
}


void ledsRainbow()
{
    analogWrite(LED_RED, 255);
    delay(200);

    analogWrite(LED_RED, 0);
    analogWrite(LED_GREEN, 255);
    delay(200);

    analogWrite(LED_GREEN, 0);
    analogWrite(LED_BLUE, 255);
    delay(200);

    analogWrite(LED_BLUE, 0);
}


void ledsGreenBlink3()
{
    for (int i = 0; i < 3; i++)
    {
        analogWrite(LED_GREEN, 255);
        delay(200);

        analogWrite(LED_GREEN, 0);
        delay(200);
    }
}


void ledsRedBlink3()
{
    for (int i = 0; i < 3; i++)
    {
        analogWrite(LED_RED, 255);
        delay(200);

        analogWrite(LED_RED, 0);
        delay(200);
    }
}


void ledsOrangeFade()
{
    // Orange = rouge + vert
    // Fade IN
    for (int brightness = 0; brightness <= 255; brightness += 5)
    {
        analogWrite(LED_RED, brightness);
        analogWrite(LED_GREEN, brightness / 2);
        delay(20);
    }

    // Fade OUT
    for (int brightness = 255; brightness >= 0; brightness -= 5)
    {
        analogWrite(LED_RED, brightness);
        analogWrite(LED_GREEN, brightness / 2);
        delay(20);
    }
}