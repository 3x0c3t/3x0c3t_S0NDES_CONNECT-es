#include "debug.h"


// ============================================================
// DEBUG GENERAL
// ============================================================

void debugStartup()
{
    Serial.println("=== HOSTNAME | DEMARRAGE ===");
}


void debugSystemReady()
{
    Serial.println("=== SYSTEME | PRET ===");
}


// ============================================================
// OLED
// ============================================================

void debugOledOk()
{
    Serial.println("=== OLED | OK ===");
}


// ============================================================
// LEDS
// ============================================================

void debugLedsInitStart()
{
    Serial.println("=== LEDS | INITIALISATION ===");
}


void debugLedsInitEnd()
{
    Serial.println("=== LEDS | INITIALISEES ===");
}


void debugLedsOff()
{
    Serial.println("=== LEDS | OFF ===");
}


void debugLedBlue()
{
    Serial.println("=== LED BLEUE ===");
}


void debugLedGreen()
{
    Serial.println("=== LED VERTE ===");
}


void debugLedRed()
{
    Serial.println("=== LED ROUGE ===");
}


void debugLedBluePin(
    uint8_t pin,
    uint8_t state
)
{
    Serial.println(
        "LED BLEUE | GPIO" +
        String(pin) +
        " = " +
        String(state)
    );
}


void debugLedGreenPin(
    uint8_t pin,
    uint8_t state
)
{
    Serial.println(
        "LED VERTE | GPIO" +
        String(pin) +
        " = " +
        String(state)
    );
}


void debugLedRedPin(
    uint8_t pin,
    uint8_t state
)
{
    Serial.println(
        "LED ROUGE | GPIO" +
        String(pin) +
        " = " +
        String(state)
    );
}


void debugLedsTestStart()
{
    Serial.println("=== LEDS | TEST ===");
}


void debugLedsTestEnd()
{
    Serial.println("=== LEDS | FIN TEST ===");
}


void debugLedGreenBlinkStart()
{
    Serial.println("=== LED VERTE | 3 CLIGNOTEMENTS ===");
}


void debugLedRedBlinkStart()
{
    Serial.println("=== LED ROUGE | 3 CLIGNOTEMENTS ===");
}


void debugLedsRainbow()
{
    Serial.println("=== LEDS | ARC-EN-CIEL ===");
}


// ============================================================
// WIFI
// ============================================================

void debugWifiStart()
{
    Serial.println("=== WIFI | CONNEXION ===");
}


void debugWifiStatus(
    const String& status
)
{
    Serial.println(
        "WIFI | STATUS : " +
        status
    );
}


void debugWifiOk()
{
    Serial.println("=== WIFI | OK ===");
}


void debugWifiFail()
{
    Serial.println("=== WIFI | FAIL ===");
}


void debugWifiSsid(
    const String& ssid
)
{
    Serial.println(
        "WIFI | SSID : " +
        ssid
    );
}


void debugWifiIp(
    const String& ip
)
{
    Serial.println(
        "WIFI | IP : " +
        ip
    );
}


void debugWifiReconnectEnabled()
{
    Serial.println(
        "WIFI | RECONNEXION AUTOMATIQUE ACTIVE"
    );
}


void debugWifiReconnected()
{
    Serial.println("=== WIFI | RECONNECTE ===");
}


void debugWifiDisconnected(
    const String& status
)
{
    Serial.println(
        "=== WIFI | DECONNECTE | " +
        status +
        " ==="
    );
}


void debugWifiReconnect(
    const String& status
)
{
    Serial.println(
        "WIFI | RECONNECT | STATUS : " +
        status
    );
}


// ============================================================
// TEMPERATURES
// ============================================================

void debugTemperatureInit()
{
    Serial.println("=== TEMPERATURE | DS18B20 ===");
}


void debugTemperatureSensorCount(
    uint8_t count
)
{
    Serial.println(
        "TEMPERATURE | SONDES : " +
        String(count)
    );
}


void debugTemperatureSensorAddress(
    uint8_t sensor,
    const uint8_t* address
)
{
    String message =
        "TEMPERATURE | S" +
        String(sensor) +
        " | ADRESSE : ";

    for (
        uint8_t i = 0;
        i < 8;
        i++
    )
    {
        if (address[i] < 16)
        {
            message += "0";
        }

        message += String(
            address[i],
            HEX
        );

        if (i < 7)
        {
            message += " ";
        }
    }

    Serial.println(message);
}


void debugTemperatureSensorAddressError(
    uint8_t sensor
)
{
    Serial.println(
        "TEMPERATURE | ERREUR ADRESSE S" +
        String(sensor)
    );
}


void debugTemperatureConversionStart()
{
    Serial.println(
        "=== TEMPERATURE | CONVERSION START ==="
    );
}


void debugTemperatureConversionEnd()
{
    Serial.println(
        "=== TEMPERATURE | CONVERSION END ==="
    );
}


void debugTemperature(
    uint8_t sensor,
    float temperature
)
{
    Serial.println(
        "TEMPERATURE | S" +
        String(sensor) +
        " : " +
        String(
            temperature,
            2
        )
    );
}


void debugTemperatureError(
    uint8_t sensor
)
{
    Serial.println(
        "TEMPERATURE | S" +
        String(sensor) +
        " : ERREUR DECONNEXION"
    );
}


// ============================================================
// SERVEUR WEB
// ============================================================

void debugWebserverInit()
{
    Serial.println(
        "=== WEBSERVER | INITIALISATION ==="
    );
}


void debugWebserverOk()
{
    Serial.println(
        "=== WEBSERVER | OK ==="
    );
}


void debugSystemReadyWeb()
{
    Serial.println(
        "=== WEBSERVER | SYSTEME PRET ==="
    );
}


void debugHttpRoot()
{
    Serial.println("HTTP | GET /");
}


void debugHttpCSS()
{
    Serial.println("HTTP | GET /style.css");
}


void debugHttpJS()
{
    Serial.println("HTTP | GET /script.js");
}


void debugHttpStatus()
{
    Serial.println("HTTP | GET /api/status");
}


void debugHttpTemperatures()
{
    Serial.println(
        "HTTP | GET /api/temperatures"
    );
}


void debugHttpLedStart()
{
    Serial.println(
        "=== HTTP | LED REQUEST ==="
    );
}


void debugHttpLedCommand(
    const String& color
)
{
    Serial.println(
        "HTTP | LED : " +
        color
    );
}


void debugHttpLedBlue()
{
    Serial.println(
        "HTTP | LED COMMAND : BLUE"
    );
}


void debugHttpLedGreen()
{
    Serial.println(
        "HTTP | LED COMMAND : GREEN"
    );
}


void debugHttpLedRed()
{
    Serial.println(
        "HTTP | LED COMMAND : RED"
    );
}


void debugHttpLedOff()
{
    Serial.println(
        "HTTP | LED COMMAND : OFF"
    );
}


void debugHttpLedEnd()
{
    Serial.println(
        "=== HTTP | LED FIN ==="
    );
}


void debugHttpBuzzerStart()
{
    Serial.println(
        "=== HTTP | BUZZER REQUEST ==="
    );
}


void debugHttpBuzzerCommand(
    const String& color
)
{
    Serial.println(
        "HTTP | BUZZER : " +
        color
    );
}


void debugHttpBuzzerRed()
{
    Serial.println(
        "HTTP | BUZZER COMMAND : RED"
    );
}


void debugHttpBuzzerGreen()
{
    Serial.println(
        "HTTP | BUZZER COMMAND : GREEN"
    );
}


void debugHttpBuzzerBlue()
{
    Serial.println(
        "HTTP | BUZZER COMMAND : BLUE"
    );
}


void debugHttpBuzzerOff()
{
    Serial.println(
        "HTTP | BUZZER COMMAND : OFF"
    );
}


void debugHttpBuzzerResponse()
{
    Serial.println(
        "HTTP | BUZZER REPONSE ENVOYEE"
    );
}


void debugHttpBuzzerEnd()
{
    Serial.println(
        "=== HTTP | BUZZER FIN ==="
    );
}


void debugHttpResponseStart()
{
    Serial.println(
        "HTTP | ENVOI REPONSE"
    );
}


void debugHttpResponseEnd()
{
    Serial.println(
        "HTTP | REPONSE ENVOYEE"
    );
}


void debugHttp404(
    const String& uri
)
{
    Serial.println(
        "HTTP | 404 : " +
        uri
    );
}


// ============================================================
// ERREURS
// ============================================================

void debugErrorMissingColor()
{
    Serial.println(
        "ERROR | ARGUMENT COLOR ABSENT"
    );
}


void debugErrorUnknownColor(
    const String& color
)
{
    Serial.println(
        "ERROR | COULEUR INCONNUE : " +
        color
    );
}


void debugErrorUnknownBuzzerColor(
    const String& color
)
{
    Serial.println(
        "ERROR | COULEUR BUZZER INCONNUE : " +
        color
    );
}


// ============================================================
// OTA
// ============================================================

void debugOtaStart()
{
    Serial.println("OTA | START");
}


void debugOtaEnd()
{
    Serial.println("OTA | END");
}


void debugOtaProgress(
    unsigned int progress,
    unsigned int total
)
{
    unsigned int percent = 0;

    if (total > 0)
    {
        percent =
            progress /
            (total / 100);
    }

    Serial.println(
        "OTA | PROGRESS : " +
        String(percent) +
        "%"
    );
}


void debugOtaError(
    uint8_t error
)
{
    Serial.println(
        "OTA | ERROR : " +
        String(error)
    );
}


void debugOtaReady()
{
    Serial.println("OTA | READY");
}


// ============================================================
// SYSTEME
// ============================================================

void debugWebserverNotStarted()
{
    Serial.println(
        "=== WEBSERVER | NON DEMARRE | WIFI NON CONNECTE ==="
    );
}