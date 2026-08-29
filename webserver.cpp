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
#include "debug.h"


// ============================================================
// SERVEUR HTTP
// ============================================================

ESP8266WebServer server(80);


// ============================================================
// TRANSMISSION DES FICHIERS PROGMEM
// ============================================================

#define WEB_SEND_BUFFER_SIZE 1024


void sendProgmemFile(
    const char* contentType,
    PGM_P content
)
{
    if (content == nullptr)
    {
        server.send(
            500,
            "text/plain",
            "Internal Server Error"
        );

        return;
    }


    const size_t contentLength = strlen_P(content);


    // --------------------------------------------------------
    // Annonce de la taille exacte du contenu
    // --------------------------------------------------------

    server.setContentLength(
        contentLength
    );


    // --------------------------------------------------------
    // Envoi des headers HTTP
    // Corps vide pour le moment
    // --------------------------------------------------------

    server.send(
        200,
        contentType,
        ""
    );


    // --------------------------------------------------------
    // Envoi du contenu PROGMEM par blocs
    // --------------------------------------------------------

    size_t offset = 0;


    while (offset < contentLength)
    {
        size_t chunkSize =
            contentLength - offset;


        if (chunkSize > WEB_SEND_BUFFER_SIZE)
        {
            chunkSize =
                WEB_SEND_BUFFER_SIZE;
        }


        server.sendContent_P(
            content + offset,
            chunkSize
        );


        offset += chunkSize;


        // ----------------------------------------------------
        // Laisser l'ESP8266 traiter le réseau
        // ----------------------------------------------------

        yield();
    }
}


// ============================================================
// PAGE HTML
// ============================================================

void handleRoot()
{
    debugHttpRoot();


    sendProgmemFile(
        "text/html",
        HTML_PAGE
    );
}


// ============================================================
// CSS
// ============================================================

void handleCSS()
{
    debugHttpCSS();


    sendProgmemFile(
        "text/css",
        cssStyle
    );
}


// ============================================================
// JAVASCRIPT
// ============================================================

void handleJS()
{
    debugHttpJS();


    sendProgmemFile(
        "application/javascript",
        JS_PAGE
    );
}


// ============================================================
// STATUS WIFI
// ============================================================

void handleStatus()
{
    debugHttpStatus();


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


// ============================================================
// TEMPERATURES
// ============================================================

void handleTemperatures()
{
    debugHttpTemperatures();


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


// ============================================================
// LED
// ============================================================

void handleLED()
{
    debugHttpLedStart();


    if (
        !server.hasArg("color")
    )
    {
        debugErrorMissingColor();


        server.send(
            400,
            "application/json",
            "{\"ok\":false,\"error\":\"missing color\"}"
        );


        debugHttpLedEnd();


        return;
    }


    String color =
        server.arg("color");


    color.toLowerCase();


    debugHttpLedCommand(
        color
    );


    // ========================================================
    // BLEU
    // ========================================================

    if (
        color == "blue"
    )
    {
        debugHttpLedBlue();


        ledBlue();
    }


    // ========================================================
    // VERT
    // ========================================================

    else if (
        color == "green"
    )
    {
        debugHttpLedGreen();


        ledGreen();
    }


    // ========================================================
    // ROUGE
    // ========================================================

    else if (
        color == "red"
    )
    {
        debugHttpLedRed();


        ledRed();
    }


    // ========================================================
    // OFF
    // ========================================================

    else if (
        color == "off"
    )
    {
        debugHttpLedOff();


        ledsOff();
    }


    // ========================================================
    // COULEUR INCONNUE
    // ========================================================

    else
    {
        debugErrorUnknownColor(
            color
        );


        server.send(
            400,
            "application/json",
            "{\"ok\":false,\"error\":\"unknown color\"}"
        );


        debugHttpLedEnd();


        return;
    }


    // ========================================================
    // REPONSE HTTP
    // ========================================================

    debugHttpResponseStart();


    server.send(
        200,
        "application/json",
        "{\"ok\":true}"
    );


    debugHttpResponseEnd();


    debugHttpLedEnd();
}


// ============================================================
// BUZZER
// ============================================================

void handleBuzzer()
{
    debugHttpBuzzerStart();


    if (
        !server.hasArg("color")
    )
    {
        debugErrorMissingColor();


        server.send(
            400,
            "application/json",
            "{\"ok\":false,\"error\":\"missing color\"}"
        );


        debugHttpBuzzerEnd();


        return;
    }


    String color =
        server.arg("color");


    color.toLowerCase();


    debugHttpBuzzerCommand(
        color
    );


    // ========================================================
    // ROUGE
    // ========================================================

    if (
        color == "red"
    )
    {
        debugHttpBuzzerRed();


        ledRed();
    }


    // ========================================================
    // VERT
    // ========================================================

    else if (
        color == "green"
    )
    {
        debugHttpBuzzerGreen();


        ledGreen();
    }


    // ========================================================
    // BLEU
    // ========================================================

    else if (
        color == "blue"
    )
    {
        debugHttpBuzzerBlue();


        ledBlue();
    }


    // ========================================================
    // OFF
    // ========================================================

    else if (
        color == "off"
    )
    {
        debugHttpBuzzerOff();


        ledsOff();
    }


    // ========================================================
    // INCONNU
    // ========================================================

    else
    {
        debugErrorUnknownBuzzerColor(
            color
        );


        server.send(
            400,
            "application/json",
            "{\"ok\":false,\"error\":\"unknown color\"}"
        );


        debugHttpBuzzerEnd();


        return;
    }


    // ========================================================
    // REPONSE
    // ========================================================

    server.send(
        200,
        "application/json",
        "{\"ok\":true}"
    );


    debugHttpBuzzerResponse();


    debugHttpBuzzerEnd();
}


// ============================================================
// 404
// ============================================================

void handleNotFound()
{
    debugHttp404(
        server.uri()
    );


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
    debugWebserverInit();


    // ========================================================
    // ROUTES PRINCIPALES
    // ========================================================

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


    // ========================================================
    // API
    // ========================================================

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


    // ========================================================
    // 404
    // ========================================================

    server.onNotFound(
        handleNotFound
    );


    // ========================================================
    // DEMARRAGE
    // ========================================================

    server.begin();


    debugWebserverOk();


    debugSystemReadyWeb();
}


// ============================================================
// BOUCLE SERVEUR
// ============================================================

void webserverLoop()
{
    server.handleClient();
}