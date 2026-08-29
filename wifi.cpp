#include "wifi.h"

#include <ESP8266WiFi.h>

#include "config.h"
#include "oled.h"
#include "bootscreen.h"
#include "buzzer.h"
#include "leds.h"


// === WIFI INIT
void wifiInit()
{
    // === MODE STATION
    WiFi.mode(
        WIFI_STA
    );


    // === HOSTNAME
    WiFi.hostname(
        HOSTNAME
    );


    // === RECONNEXION AUTOMATIQUE
    WiFi.setAutoReconnect(
        true
    );


    // === CONNEXION WIFI
    WiFi.begin(
        WIFI_SSID,
        WIFI_PASSWORD
    );


    // === ATTENTE CONNEXION
    Serial.print(
        "WiFi"
    );


    uint8_t timeout = 0;


    while (
        WiFi.status() != WL_CONNECTED &&
        timeout < WIFI_TIMEOUT
    )
    {
        delay(500);

        Serial.print(
            "."
        );

        timeout++;
    }


    Serial.println();


    // ========================================================
    // WIFI OK
    // ========================================================

    if (
        WiFi.status() == WL_CONNECTED
    )
    {
        Serial.println(
            "WiFi OK"
        );


        String ssid =
            WiFi.SSID();

        String ip =
            WiFi.localIP().toString();


        Serial.print(
            "SSID : "
        );

        Serial.println(
            ssid
        );


        Serial.print(
            "IP   : "
        );

        Serial.println(
            ip
        );


        // === BOOT WIFI
        bootWifiStatus(
            true
        );


        // === BOOT IP
        bootIpAddress(
            ip.c_str()
        );


        // === WIFI SCREEN
        wifiScreen(
            true,
            ssid,
            ip
        );


        // === CONNEXION REUSSIE
        wifiSuccessBeep();


        // === LED VERTE
        ledsGreenBlink3();
    }


    // ========================================================
    // WIFI FAIL
    // ========================================================

    else
    {
        Serial.println(
            "WiFi FAIL"
        );


        // === BOOT WIFI
        bootWifiStatus(
            false
        );


        // === WIFI SCREEN
        wifiScreen(
            false,
            "",
            ""
        );


        // === CONNEXION ECHOUEE
        wifiFailureBeep();


        // === LED ROUGE
        ledsRedBlink3();


        // === WIFI RECONNEXION
        Serial.println(
            "WiFi : reconnexion automatique active"
        );
    }
}