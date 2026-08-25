#include "wifi.h"

#include <ESP8266WiFi.h>

#include "config.h"
#include "oled.h"
#include "bootscreen.h"
#include "buzzer.h"
#include "leds.h"


void wifiInit()
{
    WiFi.mode(WIFI_STA);

    WiFi.hostname(HOSTNAME);

    WiFi.begin(
        WIFI_SSID,
        WIFI_PASSWORD
    );


    Serial.print("WiFi");


    uint8_t timeout = 0;


    while(
        WiFi.status() != WL_CONNECTED &&
        timeout < WIFI_TIMEOUT
    )
    {
        delay(500);

        Serial.print(".");

        timeout++;
    }


    Serial.println();


    if(WiFi.status() == WL_CONNECTED)
    {
        Serial.println("WiFi OK");


        String ssid = WiFi.SSID();

        String ip = WiFi.localIP().toString();


        Serial.print("SSID : ");
        Serial.println(ssid);

        Serial.print("IP   : ");
        Serial.println(ip);


        bootWifiStatus(true);

        bootIpAddress(ip.c_str());


        wifiScreen(
            true,
            ssid,
            ip
        );


        // ==========================================
        // CONNEXION WIFI REUSSIE
        // ==========================================

        wifiSuccessBeep();

        ledsGreenBlink3();
    }
    else
    {
        Serial.println("WiFi FAIL");


        bootWifiStatus(false);


        wifiScreen(
            false,
            "",
            ""
        );


        // ==========================================
        // CONNEXION WIFI ECHOUEE
        // ==========================================

        wifiFailureBeep();

        ledsOrangeFade();

        ledsRedBlink3();
    }
}