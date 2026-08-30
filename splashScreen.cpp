#include "splashScreen.h"

#include <Arduino.h>
#include <U8g2lib.h>

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled;

// === SPLASH SCREEN ===

void splashScreen()
{
    oled.clearBuffer();

    oled.setFont(
        u8g2_font_fub20_tr
    );

    oled.drawStr(
        15,
        28,
        "-3x0c3t-"
    );

    oled.setFont(
        u8g2_font_7x13_tr
    );

    oled.drawStr(
        55,
        50,
        "L4B"
    );

    oled.sendBuffer();

    delay(2000);
}