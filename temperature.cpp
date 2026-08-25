#include "temperature.h"

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "settings.h"


// ============================================================
// DS18B20
// ============================================================

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);


// ============================================================
// DONNÉES
// ============================================================

float temperatures[MAX_SENSORS];

uint8_t sensorCount = 0;


// ============================================================
// ÉTAT LECTURE NON BLOQUANTE
// ============================================================

static unsigned long conversionStart = 0;

static bool conversionRunning = false;


// Temps maximum pour une conversion DS18B20 en résolution 12 bits
static const unsigned long CONVERSION_TIME_MS = 750;


// ============================================================
// INITIALISATION
// ============================================================

void temperatureInit()
{
    sensors.begin();

    sensorCount = sensors.getDeviceCount();

    if (sensorCount > MAX_SENSORS)
    {
        sensorCount = MAX_SENSORS;
    }


    // --------------------------------------------------------
    // Lecture non bloquante
    // --------------------------------------------------------

    sensors.setWaitForConversion(false);


    Serial.println();
    Serial.println("DS18B20");

    Serial.print("Sondes : ");
    Serial.println(sensorCount);
}


// ============================================================
// LANCER UNE CONVERSION
// ============================================================

void startTemperatureConversion()
{
    if (conversionRunning)
    {
        return;
    }


    sensors.requestTemperatures();

    conversionStart = millis();

    conversionRunning = true;
}


// ============================================================
// TERMINER UNE CONVERSION
// ============================================================

void finishTemperatureConversion()
{
    if (!conversionRunning)
    {
        return;
    }


    if (millis() - conversionStart < CONVERSION_TIME_MS)
    {
        return;
    }


    // --------------------------------------------------------
    // Lecture des résultats
    // --------------------------------------------------------

    for (uint8_t i = 0; i < sensorCount; i++)
    {
        temperatures[i] =
            sensors.getTempCByIndex(i);


        Serial.print("S");
        Serial.print(i + 1);

        Serial.print(" : ");

        Serial.println(
            temperatures[i]
        );
    }


    conversionRunning = false;
}


// ============================================================
// LECTURE NON BLOQUANTE
// ============================================================

void readTemperatures()
{
    if (!conversionRunning)
    {
        startTemperatureConversion();

        return;
    }


    finishTemperatureConversion();
}