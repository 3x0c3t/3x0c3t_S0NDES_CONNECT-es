#include "leds.h"

#include <Arduino.h>

#include "settings.h"


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

    Serial.println("LEDS INIT");
}


// ============================================================
// TOUTES LES LEDS OFF
// ============================================================

void ledsOff()
{
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);

    Serial.println("LEDS OFF");
}


// ============================================================
// LED BLEUE
// ============================================================

void ledBlue()
{
    Serial.println("LED BLEUE");

    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);

    digitalWrite(LED_BLUE, HIGH);

    Serial.print("GPIO14 = ");
    Serial.println(digitalRead(LED_BLUE));
}


// ============================================================
// LED VERTE
// ============================================================

void ledGreen()
{
    Serial.println("LED VERTE");

    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_RED, LOW);

    digitalWrite(LED_GREEN, HIGH);

    Serial.print("GPIO12 = ");
    Serial.println(digitalRead(LED_GREEN));
}


// ============================================================
// LED ROUGE
// ============================================================

void ledRed()
{
    Serial.println("LED ROUGE");

    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);

    digitalWrite(LED_RED, HIGH);

    Serial.print("GPIO13 = ");
    Serial.println(digitalRead(LED_RED));
}


// ============================================================
// TEST DES LEDS AU DEMARRAGE
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

    Serial.println("LED BLEUE");

    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);

    digitalWrite(LED_BLUE, LOW);

    Serial.println("GPIO14 LOW");

    delay(1000);

    digitalWrite(LED_BLUE, HIGH);

    Serial.println("GPIO14 HIGH");

    delay(2000);

    digitalWrite(LED_BLUE, LOW);

    delay(500);


    // --------------------------------------------------------
    // VERT
    // --------------------------------------------------------

    Serial.println("LED VERTE");

    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_RED, LOW);

    digitalWrite(LED_GREEN, HIGH);

    delay(500);

    digitalWrite(LED_GREEN, LOW);

    delay(500);


    // --------------------------------------------------------
    // ROUGE
    // --------------------------------------------------------

    Serial.println("LED ROUGE");

    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);

    digitalWrite(LED_RED, HIGH);

    delay(500);

    digitalWrite(LED_RED, LOW);


    Serial.println("==============================");
    Serial.println("FIN TEST LEDS");
    Serial.println("==============================");
}


// ============================================================
// VERT : 3 CLIGNOTEMENTS
// ============================================================

void ledsGreenBlink3()
{
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(LED_BLUE, LOW);
        digitalWrite(LED_RED, LOW);

        digitalWrite(LED_GREEN, HIGH);

        delay(200);

        digitalWrite(LED_GREEN, LOW);

        delay(200);
    }
}


// ============================================================
// ROUGE : 3 CLIGNOTEMENTS
// ============================================================

void ledsRedBlink3()
{
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(LED_BLUE, LOW);
        digitalWrite(LED_GREEN, LOW);

        digitalWrite(LED_RED, HIGH);

        delay(200);

        digitalWrite(LED_RED, LOW);

        delay(200);
    }
}