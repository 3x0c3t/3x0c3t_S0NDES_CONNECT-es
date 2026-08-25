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
        CSS_PAGE
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

    json += "\"wifi\":";
    json += (WiFi.status() == WL_CONNECTED ? "true" : "false");

    json += ",\"ssid\":\"";
    json += WiFi.SSID();
    json += "\"";

    json += ",\"ip\":\"";
    json += WiFi.localIP().toString();
    json += "\"";

    json += ",\"rssi\":";
    json += String(WiFi.RSSI());

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

        json += String(temperatures[i], 2);
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
    String color = server.arg("color");

    if (color == "red")
    {
        ledsRedBlink3();
    }
    else if (color == "green")
    {
        ledsGreenBlink3();
    }
    else if (color == "orange")
    {
        ledsOrangeFade();
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
    String action = server.arg("action");

    if (action == "success")
    {
        wifiSuccessBeep();
    }
    else if (action == "failure")
    {
        wifiFailureBeep();
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
// INITIALISATION
// ============================================================

void webserverInit()
{
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

    server.begin();

    Serial.println("Webserver OK");
}


// ============================================================
// BOUCLE
// ============================================================

void webserverLoop()
{
    server.handleClient();
}