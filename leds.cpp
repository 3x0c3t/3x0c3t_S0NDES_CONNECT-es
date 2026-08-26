#include "leds.h"

#include <Arduino.h>

#include "settings.h"
#include "bootscreen.h"


// ============================================================
// ÉTAT LED
// ============================================================

static void setAllLedsOff()
{
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);
}


static void prepareLeds()
{
    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);
}


// ============================================================
// INITIALISATION
// ============================================================

void ledsInit()
{
    Serial.println();
    Serial.println(">>> ledsInit()");

    prepareLeds();

    setAllLedsOff();

    Serial.println("LED BLUE  : OFF");
    Serial.println("LED GREEN : OFF");
    Serial.println("LED RED   : OFF");

    bootLedStatus(true);
}


// ============================================================
// TOUTES LES LEDS OFF
// ============================================================

void ledsOff()
{
    prepareLeds();

    setAllLedsOff();

    Serial.println("LED : OFF");

    bootLedStatus(true);
}


// ============================================================
// BLEU
// ============================================================

void ledBlue()
{
    Serial.println(">>> ledBlue()");

    prepareLeds();

    // Éteindre les autres couleurs
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);

    // Séquence explicite du GPIO14
    digitalWrite(LED_BLUE, LOW);

    delay(20);

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

    prepareLeds();

    // Éteindre les autres couleurs
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_RED, LOW);

    // Séquence explicite du GPIO12
    digitalWrite(LED_GREEN, LOW);

    delay(20);

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

    prepareLeds();

    // Éteindre les autres couleurs
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);

    // Séquence explicite du GPIO13
    digitalWrite(LED_RED, LOW);

    delay(20);

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

    prepareLeds();

    // Bleu OFF
    digitalWrite(LED_BLUE, LOW);

    // Rouge + vert ON
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);

    delay(20);

    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, HIGH);

    Serial.print("GPIO13 RED   = ");
    Serial.println(digitalRead(LED_RED));

    Serial.print("GPIO12 GREEN = ");
    Serial.println(digitalRead(LED_GREEN));
}


// ============================================================
// TEST DES LEDS AU DÉMARRAGE
// ============================================================

void ledsTest()
{
    Serial.println();
    Serial.println("==============================");
    Serial.println("TEST LEDS");
    Serial.println("==============================");


    // --------------------------------------------------------
    // BLEU
    // --------------------------------------------------------

    Serial.println("TEST BLEU");

    ledBlue();

    delay(1000);

    ledsOff();

    delay(300);


    // --------------------------------------------------------
    // VERT
    // --------------------------------------------------------

    Serial.println("TEST VERT");

    ledGreen();

    delay(1000);

    ledsOff();

    delay(300);


    // --------------------------------------------------------
    // ROUGE
    // --------------------------------------------------------

    Serial.println("TEST ROUGE");

    ledRed();

    delay(1000);

    ledsOff();

    delay(300);


    // --------------------------------------------------------
    // ORANGE
    // --------------------------------------------------------

    Serial.println("TEST ORANGE");

    ledOrange();

    delay(1000);

    ledsOff();

    delay(300);


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
// CLIGNOTEMENT ROUGE
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

    prepareLeds();

    digitalWrite(LED_BLUE, LOW);

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

        delay(20);
    }


    setAllLedsOff();
}