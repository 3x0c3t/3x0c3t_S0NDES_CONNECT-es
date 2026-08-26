#include "leds.h"

#include <Arduino.h>

#include "settings.h"


// ============================================================
// INITIALISATION
// ============================================================

void ledsInit()
{
    Serial.println();
    Serial.println("==============================");
    Serial.println("INITIALISATION LEDS");
    Serial.println("==============================");

    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);

    Serial.println("LED BLEUE  : GPIO14");
    Serial.println("LED VERTE  : GPIO12");
    Serial.println("LED ROUGE  : GPIO13");
    Serial.println("LEDS OFF");
}


// ============================================================
// TOUTES LES LEDS OFF
// ============================================================

void ledsOff()
{
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);
}


// ============================================================
// LED BLEUE
// ============================================================

void ledBlue()
{
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);

    digitalWrite(LED_BLUE, HIGH);

    Serial.print("LED BLEUE : GPIO14 = ");
    Serial.println(digitalRead(LED_BLUE));
}


// ============================================================
// LED VERTE
// ============================================================

void ledGreen()
{
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_RED, LOW);

    digitalWrite(LED_GREEN, HIGH);

    Serial.print("LED VERTE : GPIO12 = ");
    Serial.println(digitalRead(LED_GREEN));
}


// ============================================================
// LED ROUGE
// ============================================================

void ledRed()
{
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);

    digitalWrite(LED_RED, HIGH);

    Serial.print("LED ROUGE : GPIO13 = ");
    Serial.println(digitalRead(LED_RED));
}


// ============================================================
// TEST DES LEDS AU DEMARRAGE
// ============================================================

void ledsTest()
{
    Serial.println();
    Serial.println("==============================");
    Serial.println("TEST LED DIRECT");
    Serial.println("==============================");


    // --------------------------------------------------------
    // BLEU
    // --------------------------------------------------------

    Serial.println();
    Serial.println("------------------------------");
    Serial.println("LED BLEUE");
    Serial.println("------------------------------");

    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, LOW);

    delay(500);

    digitalWrite(LED_BLUE, HIGH);

    Serial.print("GPIO14 = ");
    Serial.println(digitalRead(LED_BLUE));

    delay(3000);

    digitalWrite(LED_BLUE, LOW);

    Serial.println("GPIO14 LOW");


    // --------------------------------------------------------
    // VERT
    // --------------------------------------------------------

    Serial.println();
    Serial.println("------------------------------");
    Serial.println("LED VERTE");
    Serial.println("------------------------------");

    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);

    Serial.print("GPIO12 = ");
    Serial.println(digitalRead(LED_GREEN));

    delay(1000);

    digitalWrite(LED_GREEN, LOW);


    // --------------------------------------------------------
    // ROUGE
    // --------------------------------------------------------

    Serial.println();
    Serial.println("------------------------------");
    Serial.println("LED ROUGE");
    Serial.println("------------------------------");

    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);

    Serial.print("GPIO13 = ");
    Serial.println(digitalRead(LED_RED));

    delay(1000);

    digitalWrite(LED_RED, LOW);


    // --------------------------------------------------------
    // FIN
    // --------------------------------------------------------

    ledsOff();

    Serial.println();
    Serial.println("==============================");
    Serial.println("TEST LED TERMINE");
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
// VERT CLIGNOTEMENT x3
// ============================================================

void ledsGreenBlink3()
{
    for (int i = 0; i < 3; i++)
    {
        ledGreen();
        delay(250);

        ledsOff();
        delay(250);
    }
}


// ============================================================
// ROUGE CLIGNOTEMENT x3
// ============================================================

void ledsRedBlink3()
{
    for (int i = 0; i < 3; i++)
    {
        ledRed();
        delay(250);

        ledsOff();
        delay(250);
    }
}