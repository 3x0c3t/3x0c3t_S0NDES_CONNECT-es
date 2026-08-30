#include "oled.h"

#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

#include "config.h"
#include "settings.h"
#include "temperature.h"

#include "debug.h"


// ============================================================
// OLED
// ============================================================

U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(
    U8G2_R0,
    U8X8_PIN_NONE
);


// ============================================================
// OLED INIT
// ============================================================

void oledInit()
{
    Wire.begin(
        OLED_SDA,
        OLED_SCL
    );

    oled.begin();

    debugOledOk();
}


// ============================================================
// OLED SPLASH
// ============================================================

void oledSplash()
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
}


// ============================================================
// WIFI SCREEN
// ============================================================

void wifiScreen(
    bool ok,
    String ssid,
    String ip
)
{
    oled.clearBuffer();

    oled.setFont(
        u8g2_font_6x12_tr
    );


    // ========================================================
    // WIFI OK
    // ========================================================

    if (ok)
    {
        oled.drawStr(
            0,
            12,
            "WIFI OK"
        );

        oled.drawStr(
            0,
            27,
            "SSID:"
        );

        oled.drawStr(
            0,
            39,
            ssid.c_str()
        );

        oled.drawStr(
            0,
            54,
            "IP:"
        );

        oled.drawStr(
            20,
            54,
            ip.c_str()
        );
    }


    // ========================================================
    // WIFI ERROR
    // ========================================================

    else
    {
        oled.drawStr(
            0,
            25,
            "WIFI ERROR"
        );
    }

    oled.sendBuffer();
}


// ============================================================
// TEMPERATURE SCREEN
// ============================================================

void temperatureScreen()
{
    oled.clearBuffer();

    oled.setFont(u8g2_font_6x10_tf);

    oled.drawStr(19, 10, "1");
    oled.drawStr(62, 10, "2");
    oled.drawStr(105, 10, "3");

    oled.drawVLine(42, 0, 64);
    oled.drawVLine(85, 0, 64);

    char buffer[12];

    oled.setFont(u8g2_font_7x14B_tf);

    for (uint8_t i = 0; i < 3; i++)
    {
        if (temperatures[i] == DEVICE_DISCONNECTED_C)
        {
            snprintf(
                buffer,
                sizeof(buffer),
                "---"
            );
        }
        else
        {
            snprintf(
                buffer,
                sizeof(buffer),
                "%.1fC",
                temperatures[i]
            );
        }

        int16_t width =
            oled.getStrWidth(buffer);

        int16_t x =
            (i * 43) +
            ((43 - width) / 2);

        oled.drawStr(
            x,
            40,
            buffer
        );
    }

    oled.sendBuffer();
}