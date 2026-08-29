#include "oled.h"

#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

#include "globals.h"
#include "settings.h"
#include "config.h"


U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(
    U8G2_R0,
    U8X8_PIN_NONE
);


void oledInit()
{
    Wire.begin(OLED_SDA, OLED_SCL);

    oled.begin();
    oled.clearBuffer();
}


void oledSplash()
{
    oled.clearBuffer();

    oled.setFont(u8g2_font_fub20_tr);

    oled.drawStr(
        15,
        28,
        "-3x0c3t-"
    );

    oled.setFont(u8g2_font_7x13_tr);

    oled.drawStr(
        55,
        50,
        "L4B"
    );

    oled.sendBuffer();
}


void wifiScreen(bool ok, String ssid, String ip)
{
    oled.clearBuffer();

    oled.setFont(u8g2_font_6x12_tr);

    if(ok)
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
    else
    {
        oled.drawStr(
            0,
            25,
            "!! NO WIFI !!"
        );
    }

    oled.sendBuffer();
}


void temperatureScreen()
{
    oled.clearBuffer();

    oled.setFont(u8g2_font_5x8_mr);

    oled.drawStr(
        0,
        8,
        HOSTNAME
    );

    int y = 22;

    for(uint8_t i = 0; i < sensorCount; i++)
    {
        oled.setCursor(0, y);

        oled.print("S");
        oled.print(i + 1);
        oled.print(": ");

        oled.print(temperatures[i], 2);

        oled.print(" C");

        y += 10;
    }

    oled.sendBuffer();
}