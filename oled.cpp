#include "oled.h"

#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

#include "config.h"
#include "settings.h"


// === OLED
U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(
    U8G2_R0,
    U8X8_PIN_NONE
);


// === OLED INIT
void oledInit()
{
    Wire.begin(
        OLED_SDA,
        OLED_SCL
    );

    oled.begin();

    Serial.println(
        "OLED : OK"
    );
}


// === OLED SPLASH
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


// === WIFI SCREEN
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


    // === WIFI OK
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


    // === WIFI ERROR
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


// === TEMPERATURE SCREEN
void temperatureScreen()
{
    oled.clearBuffer();

    oled.setFont(
        u8g2_font_5x8_mr
    );

    oled.drawStr(
        0,
        8,
        "FRIGO_20260803"
    );

    int y = 22;


    // === AFFICHAGE SONDES
    for (
        uint8_t i = 0;
        i < sensorCount;
        i++
    )
    {
        oled.setCursor(
            0,
            y
        );

        oled.print(
            "S"
        );

        oled.print(
            i + 1
        );

        oled.print(
            ": "
        );

        oled.print(
            temperatures[i],
            2
        );

        oled.print(
            " C"
        );

        y += 10;
    }

    oled.sendBuffer();
}