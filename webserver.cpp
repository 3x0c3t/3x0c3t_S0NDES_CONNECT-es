#include "webserver.h"

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#include "html.h"
#include "temperature.h"
#include "leds.h"
#include "buzzer.h"

extern float temperatures[];
extern uint8_t sensorCount;

ESP8266WebServer server(80);


// ============================================================
// PAGE PRINCIPALE
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
// ÉTAT DU SYSTÈME
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
    json += String(millis());

    json += "}";

    server.send(
        200,
        "application/json",
        json
    );
}


// ============================================================
// TEMPÉRATURES
// ============================================================

void handleTemperatures()
{
    String json = "{";
    json += "\"count\":";
    json += String(sensorCount);
    json += ",\"values\":[";

    for (uint8_t i = 0; i < sensorCount; i++)
    {
        if (i > 0)
            json += ",";

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

void handleLed()
{
    if (!server.hasArg("color"))
    {
        server.send(
            400,
            "text/plain",
            "Missing color"
        );

        return;
    }

    String color = server.arg("color");

    if (color == "off")
    {
        ledsOff();
    }
    else if (color == "green")
    {
        ledsGreenBlink3();
    }
    else if (color == "red")
    {
        ledsRedBlink3();
    }
    else if (color == "orange")
    {
        ledsOrangeFade();
    }
    else if (color == "rainbow")
    {
        ledsRainbow();
    }
    else
    {
        server.send(
            400,
            "text/plain",
            "Unknown LED command"
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
            "text/plain",
            "Missing action"
        );

        return;
    }

    String action = server.arg("action");

    if (action == "beep")
    {
        beep(1200, 150);
    }
    else if (action == "success")
    {
        successBeep();
    }
    else if (action == "startup")
    {
        startupMelody();
    }
    else
    {
        server.send(
            400,
            "text/plain",
            "Unknown buzzer command"
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
        "{\"ok\":true,\"message\":\"Rebooting\"}"
    );

    delay(300);

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
        handleLed
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