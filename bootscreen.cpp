#include "bootscreen.h"

#include <Arduino.h>
#include <U8g2lib.h>

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled;

static bool ledOK = false;
static bool buzzerOK = false;
static bool wifiOK = false;
static String ipAddress = "";

static void drawBootScreen()
{
    oled.clearBuffer();

    oled.setFont(u8g2_font_6x12_tr);

    oled.drawStr(0, 10, "3x0c3t S0NDES");
    oled.drawStr(0, 21, "Version : 1.0");
    oled.drawStr(0, 32, "Date : 2026-08-25");

    oled.drawStr(
        0,
        43,
        ledOK ? "LED    : OK" : "LED    : ..."
    );

    oled.drawStr(
        0,
        54,
        buzzerOK ? "BUZZER : OK" : "BUZZER : ..."
    );

    oled.sendBuffer();
}

void bootScreen()
{
    drawBootScreen();
}

void bootLedStatus(bool ok)
{
    ledOK = ok;
    drawBootScreen();
}

void bootBuzzerStatus(bool ok)
{
    buzzerOK = ok;
    drawBootScreen();
}

void bootWifiStatus(bool ok)
{
    wifiOK = ok;
    drawBootScreen();
}

void bootIpAddress(const char* ip)
{
    ipAddress = ip;
    drawBootScreen();
}
