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

    Serial.print("BLUE  : ");
    Serial.println(digitalRead(LED_BLUE));

    Serial.print("GREEN : ");
    Serial.println(digitalRead(LED_GREEN));

    Serial.print("RED   : ");
    Serial.println(digitalRead(LED_RED));

    bootLedStatus(true);
}


// ============================================================
// BLEU
// ============================================================

void ledBlue()
{
    Serial.println(">>> ledBlue()");

    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);

    digitalWrite(LED_BLUE, LOW);
    delay(50);

    digitalWrite(LED_BLUE, HIGH);

    Serial.print("GPIO14 = ");
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

    Serial.print("GPIO13 RED   = ");
    Serial.println(digitalRead(LED_RED));

    Serial.print("GPIO12 GREEN = ");
    Serial.println(digitalRead(LED_GREEN));
}


// ============================================================
// TEST DES LEDS
// ============================================================

void ledsTest()
{
    Serial.println();
    Serial.println("==============================");
    Serial.println("TEST LEDS");
    Serial.println("==============================");


    // ========================================================
    // TEST BLEU DIRECT
    // ========================================================

    Serial.println("TEST GPIO14 DIRECT");

    pinMode(LED_BLUE, OUTPUT);

    digitalWrite(LED_BLUE, LOW);

    Serial.println("GPIO14 LOW");

    delay(2000);

    digitalWrite(LED_BLUE, HIGH);

    Serial.println("GPIO14 HIGH");

    delay(3000);

    digitalWrite(LED_BLUE, LOW);

    Serial.println("GPIO14 LOW");


    // ========================================================
    // TEST VERT
    // ========================================================

    ledGreen();

    delay(500);

    ledsOff();

    delay(300);


    // ========================================================
    // TEST ROUGE
    // ========================================================

    ledRed();

    delay(500);

    ledsOff();

    delay(300);


    // ========================================================
    // TEST ORANGE
    // ========================================================

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
// VERT CLIGNOTANT x3
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
// ROUGE CLIGNOTANT x3
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

    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);

    digitalWrite(LED_BLUE, LOW);

    // --------------------------------------------------------
    // FADE IN
    // --------------------------------------------------------

    for (int brightness = 0;
         brightness <= 255;
         brightness += 5)
    {
        analogWrite(
            LED_RED,
            brightness
        );

        analogWrite(
            LED_GREEN,
            brightness / 2
        );

        delay(20);
    }


    // --------------------------------------------------------
    // FADE OUT
    // --------------------------------------------------------

    for (int brightness = 255;
         brightness >= 0;
         brightness -= 5)
    {
        analogWrite(
            LED_RED,
            brightness
        );

        analogWrite(
            LED_GREEN,
            brightness / 2
        );

        delay(20);
    }

    ledsOff();
}