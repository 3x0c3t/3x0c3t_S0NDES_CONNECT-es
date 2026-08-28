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


// ============================================================
// SERVEUR HTTP
// ============================================================

ESP8266WebServer server(80);


// ============================================================
// PAGE HTML
// ============================================================

void handleRoot()
{
    Serial.println("HTTP GET /");

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
    Serial.println("HTTP GET /style.css");

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
    Serial.println("HTTP GET /script.js");

    server.send_P(
        200,
        "application/javascript",
        JS_PAGE
    );
}


// ============================================================
// STATUS WIFI
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
// TEMPÉRATURES
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
    Serial.println();
    Serial.println("==============================");
    Serial.println("HTTP LED REQUEST");
    Serial.println("==============================");

    if (!server.hasArg("color"))
    {
        Serial.println("ERREUR : argument color absent");

        server.send(
            400,
            "application/json",
            "{\"ok\":false,\"error\":\"missing color\"}"
        );

        Serial.println("==============================");
        Serial.println("FIN HTTP LED");
        Serial.println("==============================");

        return;
    }

    String color = server.arg("color");

    color.toLowerCase();

    Serial.print("API LED : ");
    Serial.println(color);


    // --------------------------------------------------------
    // BLEU
    // --------------------------------------------------------

    if (color == "blue")
    {
        Serial.println("COMMAND : BLUE");

        ledBlue();

        Serial.println("BLUE TERMINE");
    }


    // --------------------------------------------------------
    // VERT
    // --------------------------------------------------------

    else if (color == "green")
    {
        Serial.println("COMMAND : GREEN");

        ledGreen();

        Serial.println("GREEN TERMINE");
    }


    // --------------------------------------------------------
    // ROUGE
    // --------------------------------------------------------

    else if (color == "red")
    {
        Serial.println("COMMAND : RED");

        ledRed();

        Serial.println("RED TERMINE");
    }


    // --------------------------------------------------------
    // OFF
    // --------------------------------------------------------

    else if (color == "off")
    {
        Serial.println("COMMAND : OFF");

        ledsOff();

        Serial.println("OFF TERMINE");
    }


    // --------------------------------------------------------
    // COULEUR INCONNUE
    // --------------------------------------------------------

    else
    {
        Serial.print("COULEUR INCONNUE : ");
        Serial.println(color);

        server.send(
            400,
            "application/json",
            "{\"ok\":false,\"error\":\"unknown color\"}"
        );

        Serial.println("==============================");
        Serial.println("FIN HTTP LED");
        Serial.println("==============================");

        return;
    }


    // --------------------------------------------------------
    // RÉPONSE HTTP
    // --------------------------------------------------------

    Serial.println("ENVOI REPONSE HTTP");

    server.send(
        200,
        "application/json",
        "{\"ok\":true}"
    );

    Serial.println("REPONSE HTTP ENVOYEE");

    Serial.println("==============================");
    Serial.println("FIN HTTP LED");
    Serial.println("==============================");
}


// ============================================================
// BUZZER
// ============================================================

void handleBuzzer()
{
    Serial.println();
    Serial.println("==============================");
    Serial.println("HTTP BUZZER REQUEST");
    Serial.println("==============================");

    if (!server.hasArg("color"))
    {
        Serial.println("ERREUR : argument color absent");

        server.send(
            400,
            "application/json",
            "{\"ok\":false,\"error\":\"missing color\"}"
        );

        return;
    }

    String color = server.arg("color");

    color.toLowerCase();

    Serial.print("API BUZZER : ");
    Serial.println(color);


    // --------------------------------------------------------
    // RED
    // --------------------------------------------------------

    if (color == "red")
    {
        Serial.println("BUZZER COMMAND : RED");

        ledRed();
    }


    // --------------------------------------------------------
    // GREEN
    // --------------------------------------------------------

    else if (color == "green")
    {
        Serial.println("BUZZER COMMAND : GREEN");

        ledGreen();
    }


    // --------------------------------------------------------
    // BLUE
    // --------------------------------------------------------

    else if (color == "blue")
    {
        Serial.println("BUZZER COMMAND : BLUE");

        ledBlue();
    }


    // --------------------------------------------------------
    // OFF
    // --------------------------------------------------------

    else if (color == "off")
    {
        Serial.println("BUZZER COMMAND : OFF");

        ledsOff();
    }


    // --------------------------------------------------------
    // INCONNU
    // --------------------------------------------------------

    else
    {
        Serial.print("COULEUR BUZZER INCONNUE : ");
        Serial.println(color);

        server.send(
            400,
            "application/json",
            "{\"ok\":false,\"error\":\"unknown color\"}"
        );

        return;
    }


    server.send(
        200,
        "application/json",
        "{\"ok\":true}"
    );

    Serial.println("REPONSE BUZZER ENVOYEE");

    Serial.println("==============================");
    Serial.println("FIN HTTP BUZZER");
    Serial.println("==============================");
}


// ============================================================
// 404
// ============================================================

void handleNotFound()
{
    Serial.print("HTTP 404 : ");
    Serial.println(server.uri());

    server.send(
        404,
        "text/plain",
        "404 Not Found"
    );
}


// ============================================================
// INITIALISATION SERVEUR
// ============================================================

void webserverInit()
{
    Serial.println();
    Serial.println("==============================");
    Serial.println("INITIALISATION SERVEUR WEB");
    Serial.println("==============================");


    // --------------------------------------------------------
    // ROUTES PRINCIPALES
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


    // --------------------------------------------------------
    // 404
    // --------------------------------------------------------

    server.onNotFound(
        handleNotFound
    );


    // --------------------------------------------------------
    // DÉMARRAGE
    // --------------------------------------------------------

    server.begin();

    Serial.println("SERVEUR WEB : OK");

    Serial.println("==============================");
    Serial.println("SYSTEME PRET");
    Serial.println("==============================");
}


// ============================================================
// BOUCLE SERVEUR
// ============================================================

void webserverLoop()
{
    server.handleClient();
}