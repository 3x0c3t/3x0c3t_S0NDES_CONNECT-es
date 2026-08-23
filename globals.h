#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <U8g2lib.h>

#define MAX_SENSORS 10

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled;

extern float temperatures[MAX_SENSORS];

extern uint8_t sensorCount;

#endif