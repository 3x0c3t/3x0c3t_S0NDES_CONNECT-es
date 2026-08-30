#include "wifi.h"

#include <ESP8266WiFi.h>

#include "config.h"
#include "oled.h"
#include "bootscreen.h"
#include "buzzer.h"
#include "leds.h"
#include "debug.h"


// ============================================================
// WIFI ETAT
// ============================================================

static bool wifiConnected = false;


// ============================================================
// WIFI RECONNEXION
// ============================================================

static unsigned long lastReconnectAttempt = 0;

static const unsigned long WIFI_RECONNECT_INTERVAL = 10000;


// ============================================================
// WIFI STATUS
// ============================================================

const char* wifiStatusText(
    wl_status_t status
)
{
    switch (
        status
    )
    {
        case WL_CONNECTED:
            return "WL_CONNECTED";

        case WL_NO_SSID_AVAIL:
            return "WL_NO_SSID_AVAIL";

        case WL_CONNECT_FAILED:
            return "WL_CONNECT_FAILED";

        case WL_CONNECTION_LOST:
            return "WL_CONNECTION_LOST";

        case WL_DISCONNECTED:
            return "WL_DISCONNECTED";

        case WL_IDLE_STATUS:
            return "WL_IDLE_STATUS";

        default:
            return "UNKNOWN";
    }
}


// ============================================================
// WIFI INIT
// ============================================================

void wifiInit()
{
    debugWifiStart();


    // ========================================================
    // MODE STATION
    // ========================================================

    WiFi.mode(
        WIFI_STA
    );


    // ========================================================
    // HOSTNAME
    // ========================================================

    WiFi.hostname(
        HOSTNAME
    );


    // ========================================================
    // RECONNEXION AUTOMATIQUE
    // ========================================================

    WiFi.setAutoReconnect(
        true
    );


    // ========================================================
    // CONNEXION WIFI
    // ========================================================

    WiFi.begin(
        WIFI_SSID,
        WIFI_PASSWORD
    );


    // ========================================================
    // ATTENTE CONNEXION
    // ========================================================

    uint8_t timeout = 0;

    while (
        WiFi.status() != WL_CONNECTED &&
        timeout < WIFI_TIMEOUT
    )
    {
        delay(500);

        timeout++;
    }


    // ========================================================
    // WIFI STATUS
    // ========================================================

    String status =
        wifiStatusText(
            WiFi.status()
        );

    debugWifiStatus(
        status
    );


    // ========================================================
    // WIFI OK
    // ========================================================

    if (
        WiFi.status() == WL_CONNECTED
    )
    {
        wifiConnected =
            true;

        debugWifiOk();


        String ssid =
            WiFi.SSID();

        String ip =
            WiFi.localIP().toString();


        debugWifiSsid(
            ssid
        );

        debugWifiIp(
            ip
        );


        // ====================================================
        // BOOT WIFI
        // ====================================================

        bootWifiStatus(
            true
        );


        // ====================================================
        // BOOT IP
        // ====================================================

        bootIpAddress(
            ip.c_str()
        );


        // ====================================================
        // WIFI SCREEN
        // ====================================================

        wifiScreen(
            true,
            ssid,
            ip
        );


        // ====================================================
        // WIFI SUCCESS
        // ====================================================

        wifiSuccessBeep();


        // ====================================================
        // LED VERTE
        // ====================================================

        ledsGreenBlink3();
    }


    // ========================================================
    // WIFI FAIL
    // ========================================================

    else
    {
        wifiConnected =
            false;

        debugWifiFail();


        // ====================================================
        // BOOT WIFI
        // ====================================================

        bootWifiStatus(
            false
        );


        // ====================================================
        // WIFI SCREEN
        // ====================================================

        wifiScreen(
            false,
            "",
            ""
        );


        // ====================================================
        // WIFI FAILURE
        // ====================================================

        wifiFailureBeep();


        // ====================================================
        // LED ROUGE
        // ====================================================

        ledsRedBlink3();


        // ====================================================
        // RECONNEXION
        // ====================================================

        debugWifiReconnectEnabled();


        lastReconnectAttempt =
            millis();
    }
}


// ============================================================
// WIFI LOOP
// ============================================================

void wifiLoop()
{
    wl_status_t status =
        WiFi.status();


    // ========================================================
    // WIFI CONNECTE
    // ========================================================

    if (
        status == WL_CONNECTED
    )
    {
        // ====================================================
        // DETECTION RETOUR WIFI
        // ====================================================

        if (
            !wifiConnected
        )
        {
            wifiConnected =
                true;


            debugWifiReconnected();


            String ssid =
                WiFi.SSID();

            String ip =
                WiFi.localIP().toString();


            debugWifiSsid(
                ssid
            );

            debugWifiIp(
                ip
            );


            // =================================================
            // BOOT WIFI
            // =================================================

            bootWifiStatus(
                true
            );


            // =================================================
            // BOOT IP
            // =================================================

            bootIpAddress(
                ip.c_str()
            );


            // =================================================
            // WIFI SCREEN
            // =================================================

            wifiScreen(
                true,
                ssid,
                ip
            );


            // =================================================
            // WIFI SUCCESS
            // =================================================

            wifiSuccessBeep();


            // =================================================
            // LED VERTE
            // =================================================

            ledsGreenBlink3();
        }


        return;
    }


    // ========================================================
    // WIFI DECONNECTE
    // ========================================================

    if (
        wifiConnected
    )
    {
        wifiConnected =
            false;


        debugWifiDisconnected(
            wifiStatusText(
                status
            )
        );
    }


    // ========================================================
    // RECONNEXION
    // ========================================================

    if (
        millis() -
        lastReconnectAttempt >=
        WIFI_RECONNECT_INTERVAL
    )
    {
        lastReconnectAttempt =
            millis();


        debugWifiReconnect(
            wifiStatusText(
                status
            )
        );


        WiFi.disconnect();

        delay(50);


        WiFi.begin(
            WIFI_SSID,
            WIFI_PASSWORD
        );
    }
}