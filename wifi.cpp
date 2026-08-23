#include "wifi.h"

#include <ESP8266WiFi.h>

#include "config.h"
#include "oled.h"
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


        String ip = WiFi.localIP().toString();


        wifiScreen(true, ip);


        successBeep();


        for(int i=0;i<3;i++)
        {
            ledsRainbow();
        }

    }
    else
    {

        Serial.println("WiFi FAIL");


        wifiScreen(false,"");

    }
}