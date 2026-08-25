#ifndef OLED_H
#define OLED_H

#include <Arduino.h>

void oledInit();

void oledSplash();

void wifiScreen(bool ok, String ip);

void temperatureScreen();

#endif
