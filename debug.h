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

void debugLedsRainbow();


// ============================================================
// WIFI
// ============================================================

void debugWifiStart();

void debugWifiStatus(
    const String& status
);

void debugWifiOk();
void debugWifiFail();

void debugWifiSsid(
    const String& ssid
);

void debugWifiIp(
    const String& ip
);

void debugWifiReconnectEnabled();
void debugWifiReconnected();

void debugWifiDisconnected(
    const String& status
);

void debugWifiReconnect(
    const String& status
);


// ============================================================
// TEMPERATURES
// ============================================================

void debugTemperatureInit();

void debugTemperatureSensorCount(
    uint8_t count
);

void debugTemperatureSensorAddress(
    uint8_t sensor,
    const uint8_t* address
);

void debugTemperatureSensorAddressError(
    uint8_t sensor
);

void debugTemperatureConversionStart();
void debugTemperatureConversionEnd();

void debugTemperature(
    uint8_t sensor,
    float temperature
);

void debugTemperatureError(
    uint8_t sensor
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

void debugHttpLedBlue();
void debugHttpLedGreen();
void debugHttpLedRed();
void debugHttpLedOff();

void debugHttpLedEnd();

void debugHttpBuzzerStart();

void debugHttpBuzzerCommand(
    const String& color
);

void debugHttpBuzzerRed();
void debugHttpBuzzerGreen();
void debugHttpBuzzerBlue();
void debugHttpBuzzerOff();

void debugHttpBuzzerResponse();
void debugHttpBuzzerEnd();

void debugHttpResponseStart();
void debugHttpResponseEnd();

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

void debugErrorUnknownBuzzerColor(
    const String& color
);


// ============================================================
// OTA
// ============================================================

void debugOtaStart();
void debugOtaEnd();

void debugOtaProgress(
    unsigned int progress,
    unsigned int total
);

void debugOtaError(
    uint8_t error
);

void debugOtaReady();


// ============================================================
// SYSTEME
// ============================================================

void debugWebserverNotStarted();

#endif