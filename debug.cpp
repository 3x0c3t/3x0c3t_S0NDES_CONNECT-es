#include "debug.h"


// ============================================================
// DEBUG GENERAL
// ============================================================

void debugStartup()
{
    Serial.println();
    Serial.println("=== SONDES CONNECTEES ===");
}


void debugSystemReady()
{
    Serial.println("SYSTEME : PRET");
}


// ============================================================
// OLED
// ============================================================

void debugOledOk()
{
    Serial.println("OLED    : OK");
}


// ============================================================
// LEDS
// ============================================================

void debugLedsInitStart()
{
    Serial.println("LED     : INITIALISATION");
}


void debugLedsInitEnd()
{
    Serial.println("LED     : OK");
}


void debugLedsOff()
{
    Serial.println("LED     : OFF");
}


void debugLedBlue()
{
    Serial.println("LED     : BLUE");
}


void debugLedGreen()
{
    Serial.println("LED     : GREEN");
}


void debugLedRed()
{
    Serial.println("LED     : RED");
}


void debugLedBluePin(
    uint8_t pin,
    uint8_t state
)
{
    Serial.print("LED BLUE : GPIO");
    Serial.print(pin);
    Serial.print(" = ");
    Serial.println(state);
}


void debugLedGreenPin(
    uint8_t pin,
    uint8_t state
)
{
    Serial.print("LED GREEN: GPIO");
    Serial.print(pin);
    Serial.print(" = ");
    Serial.println(state);
}


void debugLedRedPin(
    uint8_t pin,
    uint8_t state
)
{
    Serial.print("LED RED  : GPIO");
    Serial.print(pin);
    Serial.print(" = ");
    Serial.println(state);
}


void debugLedsTestStart()
{
    Serial.println("LED TEST : START");
}


void debugLedsTestEnd()
{
    Serial.println("LED TEST : END");
}


void debugLedGreenBlinkStart()
{
    Serial.println("LED GREEN: 3 CLIGNOTEMENTS");
}


void debugLedRedBlinkStart()
{
    Serial.println("LED RED  : 3 CLIGNOTEMENTS");
}


// ============================================================
// WIFI
// ============================================================

void debugWifiStart()
{
    Serial.println("WIFI     : CONNEXION");
}


void debugWifiOk()
{
    Serial.println("WIFI     : OK");
}


void debugWifiFail()
{
    Serial.println("WIFI     : FAIL");
}


void debugWifiSsid(
    const String& ssid
)
{
    Serial.print("WIFI     : SSID = ");
    Serial.println(ssid);
}


void debugWifiIp(
    const String& ip
)
{
    Serial.print("WIFI     : IP = ");
    Serial.println(ip);
}


// ============================================================
// TEMPERATURES
// ============================================================

void debugTemperatureInit()
{
    Serial.println("TEMP     : DS18B20");
}


void debugTemperatureSensorCount(
    uint8_t count
)
{
    Serial.print("TEMP     : ");
    Serial.print(count);
    Serial.println(" SONDE(S)");
}


void debugTemperatureConversionStart()
{
    Serial.println("TEMP     : CONVERSION START");
}


void debugTemperatureConversionEnd()
{
    Serial.println("TEMP     : CONVERSION END");
}


void debugTemperature(
    uint8_t sensor,
    float temperature
)
{
    Serial.print("TEMP     : S");
    Serial.print(sensor);
    Serial.print(" = ");
    Serial.print(temperature, 2);
    Serial.println(" C");
}


// ============================================================
// SERVEUR WEB
// ============================================================

void debugWebserverInit()
{
    Serial.println("WEB      : INITIALISATION");
}


void debugWebserverOk()
{
    Serial.println("WEB      : OK");
}


void debugSystemReadyWeb()
{
    Serial.println("WEB      : SYSTEME PRET");
}


void debugHttpRoot()
{
    Serial.println("HTTP     : GET /");
}


void debugHttpCSS()
{
    Serial.println("HTTP     : GET /style.css");
}


void debugHttpJS()
{
    Serial.println("HTTP     : GET /script.js");
}


void debugHttpStatus()
{
    Serial.println("HTTP     : GET /api/status");
}


void debugHttpTemperatures()
{
    Serial.println("HTTP     : GET /api/temperatures");
}


void debugHttpLedStart()
{
    Serial.println("HTTP LED : REQUEST");
}


void debugHttpLedCommand(
    const String& color
)
{
    Serial.print("HTTP LED : ");
    Serial.println(color);
}


void debugHttpLedEnd()
{
    Serial.println("HTTP LED : OK");
}


void debugHttpBuzzerStart()
{
    Serial.println("HTTP BUZ : REQUEST");
}


void debugHttpBuzzerCommand(
    const String& action
)
{
    Serial.print("HTTP BUZ : ");
    Serial.println(action);
}


void debugHttpBuzzerEnd()
{
    Serial.println("HTTP BUZ : OK");
}


void debugHttpRebootStart()
{
    Serial.println("HTTP     : REBOOT");
}


void debugHttpRebootResponse()
{
    Serial.println("HTTP     : REBOOT RESPONSE");
}


void debugHttpRebootRestart()
{
    Serial.println("ESP      : REDEMARRAGE");
}


void debugHttp404(
    const String& uri
)
{
    Serial.print("HTTP 404 : ");
    Serial.println(uri);
}


// ============================================================
// ERREURS
// ============================================================

void debugErrorMissingColor()
{
    Serial.println("ERROR    : ARGUMENT MANQUANT");
}


void debugErrorUnknownColor(
    const String& color
)
{
    Serial.print("ERROR    : INCONNU = ");
    Serial.println(color);
}