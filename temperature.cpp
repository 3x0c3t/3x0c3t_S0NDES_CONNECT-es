#include "temperature.h"

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "config.h"
#include "settings.h"
#include "debug.h"


// ============================================================
// DS18B20
// ============================================================

OneWire oneWire(
    ONE_WIRE_BUS
);

DallasTemperature sensors(
    &oneWire
);


// ============================================================
// TEMPERATURES
// ============================================================

float temperatures[MAX_SENSORS];

uint8_t sensorCount = 0;


// ============================================================
// ADRESSES DS18B20
// ============================================================

DeviceAddress sensorAddresses[MAX_SENSORS];


// ============================================================
// CONVERSION
// ============================================================

static bool conversionRunning = false;

static unsigned long conversionStart = 0;


// ============================================================
// INTERVALLE MESURE
// ============================================================

static unsigned long lastMeasurement = 0;

static const unsigned long MEASUREMENT_INTERVAL = 5000;


// ============================================================
// TEMPS CONVERSION
// ============================================================

static const unsigned long CONVERSION_TIME_MS = 750;


// ============================================================
// INITIALISATION
// ============================================================

void temperatureInit()
{
    sensors.begin();

    debugTemperatureInit();

    sensorCount =
        sensors.getDeviceCount();

    if (
        sensorCount >
        MAX_SENSORS
    )
    {
        sensorCount =
            MAX_SENSORS;
    }

    debugTemperatureSensorCount(
        sensorCount
    );


    // ========================================================
    // RECUPERATION ADRESSES
    // ========================================================

    for (
        uint8_t i = 0;
        i < sensorCount;
        i++
    )
    {
        if (
            sensors.getAddress(
                sensorAddresses[i],
                i
            )
        )
        {
            debugTemperatureSensorAddress(
                i + 1,
                sensorAddresses[i]
            );
        }
        else
        {
            debugTemperatureSensorAddressError(
                i + 1
            );
        }
    }


    // ========================================================
    // RESOLUTION
    // ========================================================

    for (
        uint8_t i = 0;
        i < sensorCount;
        i++
    )
    {
        sensors.setResolution(
            sensorAddresses[i],
            12
        );
    }


    // ========================================================
    // CONVERSION NON BLOQUANTE
    // ========================================================

    sensors.setWaitForConversion(
        false
    );


    // ========================================================
    // INITIALISATION TEMPERATURES
    // ========================================================

    for (
        uint8_t i = 0;
        i < MAX_SENSORS;
        i++
    )
    {
        temperatures[i] =
            DEVICE_DISCONNECTED_C;
    }


    // ========================================================
    // PREMIERE MESURE IMMEDIATE
    // ========================================================

    lastMeasurement =
        millis() -
        MEASUREMENT_INTERVAL;
}


// ============================================================
// LANCER CONVERSION
// ============================================================

void startTemperatureConversion()
{
    if (
        conversionRunning
    )
    {
        return;
    }

    sensors.requestTemperatures();

    conversionStart =
        millis();

    conversionRunning =
        true;

    debugTemperatureConversionStart();
}


// ============================================================
// TERMINER CONVERSION
// ============================================================

void finishTemperatureConversion()
{
    if (
        !conversionRunning
    )
    {
        return;
    }


    // ========================================================
    // ATTENTE CONVERSION
    // ========================================================

    if (
        millis() -
        conversionStart <
        CONVERSION_TIME_MS
    )
    {
        return;
    }


    // ========================================================
    // LECTURE SONDES
    // ========================================================

    for (
        uint8_t i = 0;
        i < sensorCount;
        i++
    )
    {
        float temperature =
            sensors.getTempC(
                sensorAddresses[i]
            );


        // ====================================================
        // TEMPERATURE VALIDE
        // ====================================================

        if (
            temperature !=
            DEVICE_DISCONNECTED_C
        )
        {
            temperatures[i] =
                temperature;

            debugTemperature(
                i + 1,
                temperature
            );
        }


        // ====================================================
        // ERREUR LECTURE
        // ====================================================

        else
        {
            debugTemperatureError(
                i + 1
            );
        }
    }


    conversionRunning =
        false;

    lastMeasurement =
        millis();

    debugTemperatureConversionEnd();
}


// ============================================================
// LECTURE TEMPERATURES
// ============================================================

void readTemperatures()
{
    // ========================================================
    // CONVERSION EN COURS
    // ========================================================

    if (
        conversionRunning
    )
    {
        finishTemperatureConversion();

        return;
    }


    // ========================================================
    // ATTENTE INTERVALLE
    // ========================================================

    if (
        millis() -
        lastMeasurement <
        MEASUREMENT_INTERVAL
    )
    {
        return;
    }


    // ========================================================
    // NOUVELLE CONVERSION
    // ========================================================

    startTemperatureConversion();
}