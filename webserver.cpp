#include "webserver.h"

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#include "html.h"
#include "css.h"
#include "js.h"

#include "settings.h"
#include "temperature.h"
#include "leds.h"
#include "buzzer.h"


// ============================================================
// SERVEUR HTTP
// ============================================================

ESP8266WebServer server(80);


// ============================================================
// PAGE HTML
// ============================================================

void handleRoot()
{
    server.send(
        200,
        "text/html",
        HTML_PAGE
    );
}


// ============================================================
// CSS
// ============================================================

void handleCSS()
{
    server.send(
        200,
        "text/css",
        cssStyle
    );
}


// ============================================================
// JAVASCRIPT
// ============================================================

void handleJS()
{
    server.send(
        200,
        "application/javascript",
        JS_PAGE
    );
}


// ============================================================
// STATUS
// ============================================================

void handleStatus()
{
    String json = "{";

    // --------------------------------------------------------
    // WiFi
    // --------------------------------------------------------

    json += "\"wifi\":";
    json += (WiFi.status() == WL_CONNECTED ? "true" : "false");

    // --------------------------------------------------------
    // SSID
    // --------------------------------------------------------

    json += ",\"ssid\":\"";
    json += WiFi.SSID();
    json += "\"";

    // --------------------------------------------------------
    // IP
    // --------------------------------------------------------

    json += ",\"ip\":\"";
    json += WiFi.localIP().toString();
    json += "\"";

    // --------------------------------------------------------
    // RSSI
    // --------------------------------------------------------

    json += ",\"rssi\":";
    json += String(WiFi.RSSI());

    // --------------------------------------------------------
    // UPTIME
    // --------------------------------------------------------

    json += ",\"uptime\":";
    json += String(millis() / 1000);

    json += "}";

    server.send(
        200,
        "application/json",
        json
    );
}


// ============================================================
// TEMPERATURES
// ============================================================

void handleTemperatures()
{
    String json = "{";

    json += "\"count\":";
    json += String(sensorCount);

    json += ",\"temperatures\":[";

    for (uint8_t i = 0; i < sensorCount; i++)
    {
        if (i > 0)
        {
            json += ",";
        }

        json += String(
            temperatures[i],
            2
        );
    }

    json += "]}";

    server.send(
        200,
        "application/json",
        json
    );
}


// ============================================================
// LED
// ============================================================

void handleLED()
{
    if (!server.hasArg("color"))
    {
        server.send(
            400,
            "application/json",
            "{\"error\":\"missing color\"}"
        );

        return;
    }

    String color = server.arg("color");

    color.toLowerCase();

    // --------------------------------------------------------
    // OFF
    // --------------------------------------------------------

    if (color == "off")
    {
        ledsOff();
    }

    // --------------------------------------------------------
    // RED
    // --------------------------------------------------------

    else if (color == "red")
    {
        analogWrite(
            LED_RED,
            255
        );

        analogWrite(
            LED_GREEN,
            0
        );

        analogWrite(
            LED_BLUE,
            0
        );
    }

    // --------------------------------------------------------
    // GREEN
    // --------------------------------------------------------

    else if (color == "green")
    {
        analogWrite(
            LED_RED,
            0
        );

        analogWrite(
            LED_GREEN,
            255
        );

        analogWrite(
            LED_BLUE,
            0
        );
    }

    // --------------------------------------------------------
    // BLUE
    // --------------------------------------------------------

    else if (color == "blue")
    {
        analogWrite(
            LED_RED,
            0
        );

        analogWrite(
            LED_GREEN,
            0
        );

        analogWrite(
            LED_BLUE,
            255
        );
    }

    // --------------------------------------------------------
    // ORANGE
    // --------------------------------------------------------

    else if (color == "orange")
    {
        analogWrite(
            LED_RED,
            255
        );

        analogWrite(
            LED_GREEN,
            127
        );

        analogWrite(
            LED_BLUE,
            0
        );
    }

    // --------------------------------------------------------
    // UNKNOWN COLOR
    // --------------------------------------------------------

    else
    {
        server.send(
            400,
            "application/json",
            "{\"error\":\"unknown color\"}"
        );

        return;
    }

    server.send(
        200,
        "application/json",
        "{\"ok\":true}"
    );
}


// ============================================================
// BUZZER
// ============================================================

void handleBuzzer()
{
    if (!server.hasArg("action"))
    {
        server.send(
            400,
            "application/json",
            "{\"error\":\"missing action\"}"
        );

        return;
    }

    String action = server.arg("action");

    action.toLowerCase();

    // --------------------------------------------------------
    // TEST
    // --------------------------------------------------------

    if (action == "beep")
    {
        beep(
            1200,
            150
        );
    }

    // --------------------------------------------------------
    // SUCCESS
    // --------------------------------------------------------

    else if (action == "success")
    {
        successBeep();
    }

    // --------------------------------------------------------
    // WIFI SUCCESS
    // --------------------------------------------------------

    else if (action == "wifi-success")
    {
        wifiSuccessBeep();
    }

    // --------------------------------------------------------
    // WIFI FAILURE
    // --------------------------------------------------------

    else if (action == "wifi-failure")
    {
        wifiFailureBeep();
    }

    // --------------------------------------------------------
    // UNKNOWN ACTION
    // --------------------------------------------------------

    else
    {
        server.send(
            400,
            "application/json",
            "{\"error\":\"unknown action\"}"
        );

        return;
    }

    server.send(
        200,
        "application/json",
        "{\"ok\":true}"
    );
}


// ============================================================
// REBOOT
// ============================================================

void handleReboot()
{
    server.send(
        200,
        "application/json",
        "{\"ok\":true,\"message\":\"rebooting\"}"
    );

    delay(100);

    ESP.restart();
}


// ============================================================
// INITIALISATION SERVEUR
// ============================================================

void webserverInit()
{
    // --------------------------------------------------------
    // Pages
    // --------------------------------------------------------

    server.on(
        "/",
        HTTP_GET,
        handleRoot
    );

    server.on(
        "/style.css",
        HTTP_GET,
        handleCSS
    );

    server.on(
        "/script.js",
        HTTP_GET,
        handleJS
    );


    // --------------------------------------------------------
    // API
    // --------------------------------------------------------

    server.on(
        "/api/status",
        HTTP_GET,
        handleStatus
    );

    server.on(
        "/api/temperatures",
        HTTP_GET,
        handleTemperatures
    );

    server.on(
        "/api/led",
        HTTP_GET,
        handleLED
    );

    server.on(
        "/api/buzzer",
        HTTP_GET,
        handleBuzzer
    );

    server.on(
        "/api/reboot",
        HTTP_GET,
        handleReboot
    );


    // --------------------------------------------------------
    // 404
    // --------------------------------------------------------

    server.onNotFound(
        []()
        {
            server.send(
                404,
                "text/plain",
                "Not found: " + server.uri()
            );
        }
    );


    // --------------------------------------------------------
    // START
    // --------------------------------------------------------

    server.begin();

    Serial.println(
        "Webserver OK"
    );
}


// ============================================================
// BOUCLE SERVEUR
// ============================================================

void webserverLoop()
{
    server.handleClient();
}