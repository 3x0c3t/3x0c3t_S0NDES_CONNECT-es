#include "leds.h"
#include <Arduino.h>
#include "settings.h"


// === INITIALISATION
void ledsInit()
{
    Serial.println("=== INITIALISATION LEDS ===");

    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    ledsOff();

    Serial.print("LED BLEUE : GPIO");
    Serial.println(LED_BLUE);

    Serial.print("LED VERTE : GPIO");
    Serial.println(LED_GREEN);

    Serial.print("LED ROUGE : GPIO");
    Serial.println(LED_RED);

    Serial.println("=== LEDS INITIALISEES ===");
}


// === LEDS OFF
void ledsOff()
{
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);

    Serial.println("LEDS OFF");
}


// === LED BLEUE
void ledBlue()
{
    Serial.println("=== LED BLEUE ===");

    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, HIGH);

    Serial.print("GPIO");
    Serial.print(LED_BLUE);
    Serial.print(" = ");
    Serial.println(digitalRead(LED_BLUE));
}


// === LED VERTE
void ledGreen()
{
    Serial.println("=== LED VERTE ===");

    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);

    Serial.print("GPIO");
    Serial.print(LED_GREEN);
    Serial.print(" = ");
    Serial.println(digitalRead(LED_GREEN));
}


// === LED ROUGE
void ledRed()
{
    Serial.println("=== LED ROUGE ===");

    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);

    Serial.print("GPIO");
    Serial.print(LED_RED);
    Serial.print(" = ");
    Serial.println(digitalRead(LED_RED));
}


// === TEST LEDS
void ledsTest()
{
    Serial.println("=== TEST LEDS ===");

    // === LED BLEUE
    ledBlue();
    delay(1000);

    // === LED VERTE
    ledGreen();
    delay(1000);

    // === LED ROUGE
    ledRed();
    delay(1000);

    // === LEDS OFF
    ledsOff();

    Serial.println("=== FIN TEST LEDS ===");
}


// === ARC-EN-CIEL
void ledsRainbow()
{
    Serial.println("=== ARC-EN-CIEL ===");

    // === LED ROUGE
    ledRed();
    delay(500);

    // === LED VERTE
    ledGreen();
    delay(500);

    // === LED BLEUE
    ledBlue();
    delay(500);

    // === LEDS OFF
    ledsOff();
}


// === VERT : 3 CLIGNOTEMENTS
void ledsGreenBlink3()
{
    Serial.println("=== LED VERTE : 3 CLIGNOTEMENTS ===");

    for (int i = 0; i < 3; i++)
    {
        // === LED VERTE ON
        ledGreen();
        delay(250);

        // === LED OFF
        ledsOff();
        delay(250);
    }
}


// === ROUGE : 3 CLIGNOTEMENTS
void ledsRedBlink3()
{
    Serial.println("=== LED ROUGE : 3 CLIGNOTEMENTS ===");

    for (int i = 0; i < 3; i++)
    {
        // === LED ROUGE ON
        ledRed();
        delay(250);

        // === LED OFF
        ledsOff();
        delay(250);
    }
}