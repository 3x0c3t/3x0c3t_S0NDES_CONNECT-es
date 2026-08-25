#ifndef OLED_H
#define OLED_H

#include <Arduino.h>

void oledInit();

void wifiScreen(bool ok, String ssid, String ip);

void temperatureScreen();

#endif