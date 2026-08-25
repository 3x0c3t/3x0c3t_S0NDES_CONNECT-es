#include "bootScreen.h"

#include <Arduino.h>
#include <U8g2lib.h>

#include "settings.h"
#include "globals.h"

// Objet OLED défini dans oled.cpp
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled;

void bootScreen()
{
    oled.clearBuffer();

    // -------------------------
    // Informations firmware
    // -------------------------

    oled.setFont(u8g2_font_6x12_tr);

    oled.drawStr(0, 11, "3x0c3t S0NDES");

    oled.drawStr(0, 23, "Version : 1.0");

    oled.drawStr(0, 35, "Date : 2026-08-25");


    // -------------------------
    // Etats système
    // -------------------------

    oled.drawStr(0, 48, "LED    : ...");

    oled.drawStr(0, 59, "BUZZER : ...");

    oled.sendBuffer();
}