#include "webserver.h"

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#include "html.h"
#include "css.h"
#include "js.h"
#include "leds.h"
#include "buzzer.h"
#include "temperature.h"


// === SERVEUR HTTP
ESP8266WebServer server(80);


// === PAGE HTML
void handleRoot()
{
    Serial.println("HTTP GET /");

    size_t contentLength = strlen_P(HTML_PAGE);

    Serial.print("HTML LENGTH : ");
    Serial.println(contentLength);

    server.send_P(
        200,
        "text/html",
        HTML_PAGE,
        contentLength
    );
}


// === CSS
void handleCSS()
{
    Serial.println("HTTP GET /style.css");

    size_t contentLength = strlen_P(cssStyle);

    Serial.print("CSS LENGTH : ");
    Serial.println(contentLength);

    server.send_P(
        200,
        "text/css",
        cssStyle,
        contentLength
    );
}


// === JAVASCRIPT
void handleJS()
{
    Serial.println("HTTP GET /script.js");

    size_t contentLength = strlen_P(JS_PAGE);

    Serial.print("JS LENGTH : ");
    Serial.println(contentLength);

    server.send_P(
        200,
        "application/javascript",
        JS_PAGE,
        contentLength
    );
}


// === STATUS WIFI
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
    json += String(
        WiFi.RSSI()
    );

    json += ",\"uptime\":";
    json += String(
        millis() / 1000
    );

    json += "}";

    server.send(
        200,
        "application/json",
        json
    );
}


// === TEMPERATURES
void handleTemperatures()
{
    String json = "{";

    json += "\"count\":";
    json += String(
        sensorCount
    );

    json += ",\"temperatures\":[";

    for (
        uint8_t i = 0;
        i < sensorCount;
        i++
    )
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


// === LED
void handleLED()
{
    Serial.println();
    Serial.println("=== HTTP LED REQUEST ===");


    // === VERIFICATION ARGUMENT
    if (!server.hasArg("color"))
    {
        Serial.println(
            "ERREUR : argument color absent"
        );

        server.send(
            400,
            "application/json",
            "{\"ok\":false,\"error\":\"missing color\"}"
        );

        Serial.println("=== HTTP LED END ===");

        return;
    }


    // === RECUPERATION COULEUR
    String color = server.arg(
        "color"
    );

    color.toLowerCase();

    Serial.print(
        "API LED : "
    );

    Serial.println(
        color
    );


    // === LED BLEUE
    if (color == "blue")
    {
        Serial.println(
            "COMMAND : BLUE"
        );

        ledBlue();

        Serial.println(
            "BLUE TERMINE"
        );
    }


    // === LED VERTE
    else if (color == "green")
    {
        Serial.println(
            "COMMAND : GREEN"
        );

        ledGreen();

        Serial.println(
            "GREEN TERMINE"
        );
    }


    // === LED ROUGE
    else if (color == "red")
    {
        Serial.println(
            "COMMAND : RED"
        );

        ledRed();

        Serial.println(
            "RED TERMINE"
        );
    }


    // === LED OFF
    else if (color == "off")
    {
        Serial.println(
            "COMMAND : OFF"
        );

        ledsOff();

        Serial.println(
            "OFF TERMINE"
        );
    }


    // === COULEUR INCONNUE
    else
    {
        Serial.print(
            "COULEUR INCONNUE : "
        );

        Serial.println(
            color
        );

        server.send(
            400,
            "application/json",
            "{\"ok\":false,\"error\":\"unknown color\"}"
        );

        Serial.println(
            "=== HTTP LED END ==="
        );

        return;
    }


    // === REPONSE HTTP
    server.send(
        200,
        "application/json",
        "{\"ok\":true}"
    );

    Serial.println(
        "REPONSE LED ENVOYEE"
    );

    Serial.println(
        "=== HTTP LED END ==="
    );
}


// === BUZZER
void handleBuzzer()
{
    Serial.println();
    Serial.println(
        "=== HTTP BUZZER REQUEST ==="
    );


    // === VERIFICATION ARGUMENT
    if (!server.hasArg("action"))
    {
        Serial.println(
            "ERREUR : argument action absent"
        );

        server.send(
            400,
            "application/json",
            "{\"ok\":false,\"error\":\"missing action\"}"
        );

        Serial.println(
            "=== HTTP BUZZER END ==="
        );

        return;
    }


    // === RECUPERATION ACTION
    String action = server.arg(
        "action"
    );

    action.toLowerCase();

    Serial.print(
        "API BUZZER : "
    );

    Serial.println(
        action
    );


    // === BUZZER ON
    if (action == "on")
    {
        Serial.println(
            "BUZZER : ON"
        );

        digitalWrite(
            BUZZER_PIN,
            HIGH
        );
    }


    // === BUZZER OFF
    else if (action == "off")
    {
        Serial.println(
            "BUZZER : OFF"
        );

        digitalWrite(
            BUZZER_PIN,
            LOW
        );
    }


    // === BUZZER BEEP
    else if (action == "beep")
    {
        Serial.println(
            "BUZZER : BEEP"
        );

        digitalWrite(
            BUZZER_PIN,
            HIGH
        );

        delay(150);

        digitalWrite(
            BUZZER_PIN,
            LOW
        );
    }


    // === ACTION INCONNUE
    else
    {
        Serial.print(
            "ACTION BUZZER INCONNUE : "
        );

        Serial.println(
            action
        );

        server.send(
            400,
            "application/json",
            "{\"ok\":false,\"error\":\"unknown action\"}"
        );

        Serial.println(
            "=== HTTP BUZZER END ==="
        );

        return;
    }


    // === REPONSE HTTP
    server.send(
        200,
        "application/json",
        "{\"ok\":true}"
    );

    Serial.println(
        "REPONSE BUZZER ENVOYEE"
    );

    Serial.println(
        "=== HTTP BUZZER END ==="
    );
}


// === 404
void handleNotFound()
{
    Serial.print(
        "HTTP 404 : "
    );

    Serial.println(
        server.uri()
    );

    server.send(
        404,
        "text/plain",
        "404 Not Found"
    );
}


// === SETUP - START
void webserverInit()
{
    Serial.println();
    Serial.println(
        "=== INITIALISATION SERVEUR WEB ==="
    );


    // === ROUTE PAGE PRINCIPALE
    server.on(
        "/",
        HTTP_GET,
        handleRoot
    );


    // === ROUTE CSS
    server.on(
        "/style.css",
        HTTP_GET,
        handleCSS
    );


    // === ROUTE JAVASCRIPT
    server.on(
        "/script.js",
        HTTP_GET,
        handleJS
    );


    // === API STATUS
    server.on(
        "/api/status",
        HTTP_GET,
        handleStatus
    );


    // === API TEMPERATURES
    server.on(
        "/api/temperatures",
        HTTP_GET,
        handleTemperatures
    );


    // === API LED
    server.on(
        "/api/led",
        HTTP_GET,
        handleLED
    );


    // === API BUZZER
    server.on(
        "/api/buzzer",
        HTTP_GET,
        handleBuzzer
    );


    // === ROUTE 404
    server.onNotFound(
        handleNotFound
    );


    // === SERVEUR START
    server.begin();

    Serial.println(
        "SERVEUR WEB : OK"
    );

    Serial.println(
        "=== SETUP - END"
    );
}


// === LOOP
void webserverLoop()
{
    server.handleClient();
}