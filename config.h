#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <U8g2lib.h>

// === SYSTEME
#define SERIAL_BAUDRATE 115200
#define HOSTNAME "S0NDES_CONNECTEES"

// === WIFI
#define WIFI_TIMEOUT 30
// SSID & PWD [1]
#define WIFI_SSID "N0wifiHere"
#define WIFI_PASSWORD "@PassWeurd"
// SSID & PWD [2]
#define WIFI_SSID2 "2"
#define WIFI_PASSWORD2 "2"

// === LEDS / BUZZER
#define READY_BLINK_COUNT 3

// === TEMPERATURES
#define MAX_SENSORS 10

// === OLED GLOBAL
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled;

// === TEMPERATURES GLOBAL
extern float temperatures[MAX_SENSORS];

extern uint8_t sensorCount;

#endif