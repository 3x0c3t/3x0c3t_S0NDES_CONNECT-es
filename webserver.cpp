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
// PAGE HTML
// ============================================================

void handleRoot()
{
    debugHttpRoot();

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
    debugHttpCSS();

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
    debugHttpJS();

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


    // ========================================================
    // VERIFICATION ACTION
    // ========================================================

    if (
        !server.hasArg("action")
    )
    {
        debugErrorMissingColor();

        server.send(
            400,
            "application/json",
            "{\"ok\":false,\"error\":\"missing action\"}"
        );

        debugHttpBuzzerEnd();

        return;
    }


    String action =
        server.arg("action");

    action.toLowerCase();


    debugHttpBuzzerCommand(
        action
    );


    // ========================================================
    // BEEP SIMPLE
    // ========================================================

    if (
        action == "beep"
    )
    {
        simpleBeep();
    }


    // ========================================================
    // SUCCESS
    // ========================================================

    else if (
        action == "success"
    )
    {
        successBeep();
    }


    // ========================================================
    // WIFI OK
    // ========================================================

    else if (
        action == "wifi"
    )
    {
        wifiSuccessBeep();
    }


    // ========================================================
    // ERREUR
    // ========================================================

    else if (
        action == "error"
    )
    {
        wifiFailureBeep();
    }


    // ========================================================
    // ACTION INCONNUE
    // ========================================================

    else
    {
        debugErrorUnknownBuzzerColor(
            action
        );

        server.send(
            400,
            "application/json",
            "{\"ok\":false,\"error\":\"unknown action\"}"
        );

        debugHttpBuzzerEnd();

        return;
    }


    // ========================================================
    // REPONSE HTTP
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
    // API STATUS
    // ========================================================

    server.on(
        "/api/status",
        HTTP_GET,
        handleStatus
    );


    // ========================================================
    // API TEMPERATURES
    // ========================================================

    server.on(
        "/api/temperatures",
        HTTP_GET,
        handleTemperatures
    );


    // ========================================================
    // API LED
    // ========================================================

    server.on(
        "/api/led",
        HTTP_GET,
        handleLED
    );


    // ========================================================
    // API BUZZER
    // ========================================================

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