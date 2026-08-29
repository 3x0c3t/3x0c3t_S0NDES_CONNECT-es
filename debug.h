#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>


// ============================================================
// DEBUG GENERAL
// ============================================================

void debugStartup();
void debugSystemReady();


// ============================================================
// OLED
// ============================================================

void debugOledOk();


// ============================================================
// LEDS
// ============================================================

void debugLedsInitStart();
void debugLedsInitEnd();
void debugLedsOff();

void debugLedBlue();
void debugLedGreen();
void debugLedRed();

void debugLedBluePin(
    uint8_t pin,
    uint8_t state
);

void debugLedGreenPin(
    uint8_t pin,
    uint8_t state
);

void debugLedRedPin(
    uint8_t pin,
    uint8_t state
);

void debugLedsTestStart();
void debugLedsTestEnd();

void debugLedGreenBlinkStart();
void debugLedRedBlinkStart();


// ============================================================
// WIFI
// ============================================================

void debugWifiStart();
void debugWifiOk();
void debugWifiFail();

void debugWifiSsid(
    const String& ssid
);

void debugWifiIp(
    const String& ip
);


// ============================================================
// TEMPERATURES
// ============================================================

void debugTemperatureInit();

void debugTemperatureSensorCount(
    uint8_t count
);

void debugTemperatureConversionStart();
void debugTemperatureConversionEnd();

void debugTemperature(
    uint8_t sensor,
    float temperature
);


// ============================================================
// SERVEUR WEB
// ============================================================

void debugWebserverInit();
void debugWebserverOk();
void debugSystemReadyWeb();

void debugHttpRoot();
void debugHttpCSS();
void debugHttpJS();
void debugHttpStatus();
void debugHttpTemperatures();

void debugHttpLedStart();

void debugHttpLedCommand(
    const String& color
);

void debugHttpLedEnd();

void debugHttpBuzzerStart();

void debugHttpBuzzerCommand(
    const String& action
);

void debugHttpBuzzerEnd();

void debugHttpRebootStart();
void debugHttpRebootResponse();
void debugHttpRebootRestart();

void debugHttp404(
    const String& uri
);


// ============================================================
// ERREURS
// ============================================================

void debugErrorMissingColor();

void debugErrorUnknownColor(
    const String& color
);

#endif