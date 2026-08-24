#ifndef BUZZER_H
#define BUZZER_H


void buzzerInit();

void beep(int freq, int duration);

void startupMelody();

void successBeep();

void wifiSuccessBeep();

void wifiFailureBeep();


#endif