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
    server.send_P(
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
    server.send_P(
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
    server.send_P(
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
    json += (
        WiFi.status() == WL_CONNECTED
        ? "true"
        : "false"
    );

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
            "{\"ok\":false,\"error\":\"missing color\"}"
        );

        return;
    }

    String color = server.arg("color");

    if (color == "red")
    {
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_BLUE, LOW);
    }
    else if (color == "green")
    {
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_BLUE, LOW);
    }
    else if (color == "blue")
    {
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_BLUE, HIGH);
    }
    else if (color == "off")
    {
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_BLUE, LOW);
    }
    else
    {
        server.send(
            400,
            "application/json",
            "{\"ok\":false,\"error\":\"invalid color\"}"
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
            "{\"ok\":false,\"error\":\"missing action\"}"
        );

        return;
    }

    String action = server.arg("action");

    if (action == "on")
    {
        digitalWrite(BUZZER_PIN, HIGH);
    }
    else if (action == "off")
    {
        digitalWrite(BUZZER_PIN, LOW);
    }
    else if (action == "beep")
    {
        digitalWrite(BUZZER_PIN, HIGH);

        delay(150);

        digitalWrite(BUZZER_PIN, LOW);
    }
    else
    {
        server.send(
            400,
            "application/json",
            "{\"ok\":false,\"error\":\"invalid action\"}"
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
// NOT FOUND
// ============================================================

void handleNotFound()
{
    server.send(
        404,
        "text/plain",
        "Not found: " + server.uri()
    );
}


// ============================================================
// INITIALISATION
// ============================================================

void webserverInit()
{
    // --------------------------------------------------------
    // PAGE PRINCIPALE
    // --------------------------------------------------------

    server.on(
        "/",
        HTTP_GET,
        handleRoot
    );


    // --------------------------------------------------------
    // CSS
    // --------------------------------------------------------

    server.on(
        "/style.css",
        HTTP_GET,
        handleCSS
    );


    // --------------------------------------------------------
    // JAVASCRIPT
    // --------------------------------------------------------

    server.on(
        "/script.js",
        HTTP_GET,
        handleJS
    );


    // --------------------------------------------------------
    // API STATUS
    // --------------------------------------------------------

    server.on(
        "/api/status",
        HTTP_GET,
        handleStatus
    );


    // --------------------------------------------------------
    // API TEMPERATURES
    // --------------------------------------------------------

    server.on(
        "/api/temperatures",
        HTTP_GET,
        handleTemperatures
    );


    // --------------------------------------------------------
    // API LED
    // --------------------------------------------------------

    server.on(
        "/api/led",
        HTTP_GET,
        handleLED
    );


    // --------------------------------------------------------
    // API BUZZER
    // --------------------------------------------------------

    server.on(
        "/api/buzzer",
        HTTP_GET,
        handleBuzzer
    );


    // --------------------------------------------------------
    // API REBOOT
    // --------------------------------------------------------

    server.on(
        "/api/reboot",
        HTTP_GET,
        handleReboot
    );


    // --------------------------------------------------------
    // 404
    // --------------------------------------------------------

    server.onNotFound(
        handleNotFound
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
// BOUCLE
// ============================================================

void webserverLoop()
{
    server.handleClient();
}