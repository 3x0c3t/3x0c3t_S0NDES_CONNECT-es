#include "buzzer.h"
#include "settings.h"
#include <Arduino.h>


void buzzerInit()
{
    pinMode(BUZZER_PIN, OUTPUT);
    noTone(BUZZER_PIN);
}


void beep(int freq, int duration)
{
    tone(BUZZER_PIN, freq, duration);
    delay(duration);
    noTone(BUZZER_PIN);
    delay(50);
}


void startupMelody()
{
    beep(523, 150);   // Do
    beep(659, 150);   // Mi
    beep(784, 250);   // Sol
}


void successBeep()
{
    beep(1200, 100);
    beep(1600, 150);
}


void wifiSuccessBeep()
{
    beep(1400, 100);
    beep(1600, 100);
    beep(1800, 150);
}


void wifiFailureBeep()
{
    beep(700, 120);
    beep(600, 120);
    beep(500, 180);
}