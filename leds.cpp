#include "leds.h"
#include "defines.h"
#include <Arduino.h>

void ledsInit()
{
    pinMode(LED_BLUE,OUTPUT);
    pinMode(LED_GREEN,OUTPUT);
    pinMode(LED_RED,OUTPUT);

    ledsOff();
}

void ledsOff()
{
    digitalWrite(LED_BLUE,LOW);
    digitalWrite(LED_GREEN,LOW);
    digitalWrite(LED_RED,LOW);
}

void ledsTest()
{
    digitalWrite(LED_BLUE,HIGH);
    delay(300);
    digitalWrite(LED_BLUE,LOW);


    digitalWrite(LED_GREEN,HIGH);
    delay(300);
    digitalWrite(LED_GREEN,LOW);


    digitalWrite(LED_RED,HIGH);
    delay(300);
    digitalWrite(LED_RED,LOW);
}

void ledsRainbow()
{
    digitalWrite(LED_RED,HIGH);
    delay(200);

    digitalWrite(LED_RED,LOW);
    digitalWrite(LED_GREEN,HIGH);
    delay(200);

    digitalWrite(LED_GREEN,LOW);
    digitalWrite(LED_BLUE,HIGH);
    delay(200);

    digitalWrite(LED_BLUE,LOW);
}