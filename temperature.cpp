#include "temperature.h"

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "config.h"
#include "settings.h"
#include "debug.h"

OneWire oneWire(
    ONE_WIRE_BUS
);

DallasTemperature sensors(
    &oneWire
);

float temperatures[MAX_SENSORS];

uint8_t sensorCount = 0;

DeviceAddress sensorAddresses[MAX_SENSORS];

static bool conversionRunning = false;

static unsigned long conversionStart = 0;

static unsigned long lastMeasurement = 0;

static const unsigned long MEASUREMENT_INTERVAL = 5000;

static const unsigned long CONVERSION_TIME_MS = 750;

// === INITIALISATION TEMPERATURES ===

void temperatureInit()
{
    sensors.begin();

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

    debugTemperatureInit();

    debugTemperatureSensorCount(
        sensorCount
    );

    // === RECUPERATION ADRESSES ===

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

    // === RESOLUTION ===

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

    // === CONVERSION NON BLOQUANTE ===

    sensors.setWaitForConversion(
        false
    );

    // === VALEURS INITIALES ===

    for (
        uint8_t i = 0;
        i < MAX_SENSORS;
        i++
    )
    {
        temperatures[i] =
            DEVICE_DISCONNECTED_C;
    }

    // === PREMIERE MESURE ===

    if (
        sensorCount > 0
    )
    {
        startTemperatureConversion();

        delay(
            CONVERSION_TIME_MS
        );

        finishTemperatureConversion();
    }

    lastMeasurement =
        millis();
}

// === LANCER CONVERSION ===

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

// === TERMINER CONVERSION ===

void finishTemperatureConversion()
{
    if (
        !conversionRunning
    )
    {
        return;
    }

    if (
        millis() -
        conversionStart <
        CONVERSION_TIME_MS
    )
    {
        return;
    }

    // === LECTURE DES SONDES ===

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

// === LECTURE TEMPERATURES ===

void readTemperatures()
{
    if (
        conversionRunning
    )
    {
        finishTemperatureConversion();

        return;
    }

    if (
        millis() -
        lastMeasurement <
        MEASUREMENT_INTERVAL
    )
    {
        return;
    }

    startTemperatureConversion();
}