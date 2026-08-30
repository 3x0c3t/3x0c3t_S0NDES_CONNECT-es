#include "bootscreen.h"

#include <Arduino.h>
#include <U8g2lib.h>

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled;

static bool ledOK = false;
static bool buzzerOK = false;
static bool wifiOK = false;

static String ipAddress = "";

// === BOOT SCREEN ===

static void drawBootScreen()
{
    oled.clearBuffer();

    oled.setFont(
        u8g2_font_6x12_tr
    );

    oled.drawStr(
        0,
        10,
        "3x0c3t S0NDES"
    );

    oled.drawStr(
        0,
        21,
        "Version : 1.0"
    );

    oled.drawStr(
        0,
        32,
        "Date : 2026-08-25"
    );

    oled.drawStr(
        0,
        43,
        ledOK
            ? "LED    : OK"
            : "LED    : ..."
    );

    oled.drawStr(
        0,
        54,
        buzzerOK
            ? "BUZZER : OK"
            : "BUZZER : ..."
    );

    if (
        wifiOK &&
        ipAddress.length() > 0
    )
    {
        oled.setFont(
            u8g2_font_5x8_tr
        );

        oled.drawStr(
            0,
            63,
            ipAddress.c_str()
        );
    }

    oled.sendBuffer();
}

// === BOOT SCREEN INIT ===

void bootScreen()
{
    drawBootScreen();
}

// === LED STATUS ===

void bootLedStatus(
    bool ok
)
{
    ledOK = ok;

    drawBootScreen();
}

// === BUZZER STATUS ===

void bootBuzzerStatus(
    bool ok
)
{
    buzzerOK = ok;

    drawBootScreen();
}

// === WIFI STATUS ===

void bootWifiStatus(
    bool ok
)
{
    wifiOK = ok;

    drawBootScreen();
}

// === IP ADDRESS ===

void bootIpAddress(
    const char* ip
)
{
    ipAddress = ip;

    drawBootScreen();
}