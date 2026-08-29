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
    Serial.print("GPIO");
    Serial.print(pin);
    Serial.print(" = ");
    Serial.println(state);
}


void debugLedGreenPin(
    uint8_t pin,
    uint8_t state
)
{
    Serial.print("GPIO");
    Serial.print(pin);
    Serial.print(" = ");
    Serial.println(state);
}


void debugLedRedPin(
    uint8_t pin,
    uint8_t state
)
{
    Serial.print("GPIO");
    Serial.print(pin);
    Serial.print(" = ");
    Serial.println(state);
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


// ============================================================
// WIFI
// ============================================================

void debugWifiStart()
{
    Serial.print("=== WIFI | CONNEXION");
}


void debugWifiOk()
{
    Serial.println(" === WIFI | OK ===");
}


void debugWifiFail()
{
    Serial.println(" === WIFI | FAIL ===");
}


void debugWifiSsid(
    const String& ssid
)
{
    Serial.print("WIFI | SSID : ");
    Serial.println(ssid);
}


void debugWifiIp(
    const String& ip
)
{
    Serial.print("WIFI | IP : ");
    Serial.println(ip);
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
    Serial.print("TEMPERATURE | SONDES : ");
    Serial.println(count);
}


void debugTemperatureConversionStart()
{
    Serial.println("=== TEMPERATURE | CONVERSION START ===");
}


void debugTemperatureConversionEnd()
{
    Serial.println("=== TEMPERATURE | CONVERSION END ===");
}


void debugTemperature(
    uint8_t sensor,
    float temperature
)
{
    Serial.print("TEMPERATURE | S");
    Serial.print(sensor);
    Serial.print(" : ");
    Serial.println(
        temperature,
        2
    );
}


// ============================================================
// SERVEUR WEB
// ============================================================

void debugWebserverInit()
{
    Serial.println("=== WEBSERVER | INITIALISATION ===");
}


void debugWebserverOk()
{
    Serial.println("=== WEBSERVER | OK ===");
}


void debugSystemReadyWeb()
{
    Serial.println("=== WEBSERVER | SYSTEME PRET ===");
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
    Serial.println("HTTP | GET /api/temperatures");
}


void debugHttpLedStart()
{
    Serial.println("=== HTTP | LED REQUEST ===");
}


void debugHttpLedCommand(
    const String& color
)
{
    Serial.print("HTTP | LED : ");
    Serial.println(color);
}


void debugHttpLedEnd()
{
    Serial.println("=== HTTP | LED FIN ===");
}


void debugHttpBuzzerStart()
{
    Serial.println("=== HTTP | BUZZER REQUEST ===");
}


void debugHttpBuzzerCommand(
    const String& color
)
{
    Serial.print("HTTP | BUZZER : ");
    Serial.println(color);
}


void debugHttpBuzzerEnd()
{
    Serial.println("=== HTTP | BUZZER FIN ===");
}


void debugHttpRebootStart()
{
    Serial.println("=== HTTP | REBOOT REQUEST ===");
}


void debugHttpRebootResponse()
{
    Serial.println("HTTP | REBOOT RESPONSE");
}


void debugHttpRebootRestart()
{
    Serial.println("=== ESP | REDEMARRAGE ===");
}


void debugHttp404(
    const String& uri
)
{
    Serial.print("HTTP | 404 : ");
    Serial.println(uri);
}


// ============================================================
// ERREURS
// ============================================================

void debugErrorMissingColor()
{
    Serial.println("ERROR | ARGUMENT COLOR ABSENT");
}


void debugErrorUnknownColor(
    const String& color
)
{
    Serial.print("ERROR | COULEUR INCONNUE : ");
    Serial.println(color);
}