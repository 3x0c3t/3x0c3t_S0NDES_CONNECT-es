#include "temperature.h"

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "config.h"
#include "settings.h"


// === DS18B20
OneWire oneWire(
    ONE_WIRE_BUS
);

DallasTemperature sensors(
    &oneWire
);


// === TEMPERATURES
float temperatures[MAX_SENSORS];

uint8_t sensorCount = 0;


// === ADRESSES DS18B20
DeviceAddress sensorAddresses[MAX_SENSORS];


// === CONVERSION
static bool conversionRunning = false;

static unsigned long conversionStart = 0;


// === INTERVALLE MESURE
static unsigned long lastMeasurement = 0;

static const unsigned long MEASUREMENT_INTERVAL = 5000;


// === TEMPS CONVERSION
static const unsigned long CONVERSION_TIME_MS = 750;


// === AFFICHER ADRESSE
void printSensorAddress(
    DeviceAddress address
)
{
    for (
        uint8_t i = 0;
        i < 8;
        i++
    )
    {
        if (
            address[i] < 16
        )
        {
            Serial.print(
                "0"
            );
        }

        Serial.print(
            address[i],
            HEX
        );

        if (
            i < 7
        )
        {
            Serial.print(
                " "
            );
        }
    }
}


// === INITIALISATION
void temperatureInit()
{
    sensors.begin();


    // === NOMBRE SONDES
    sensorCount =
        sensors.getDeviceCount();


    // === LIMITE SONDES
    if (
        sensorCount >
        MAX_SENSORS
    )
    {
        sensorCount =
            MAX_SENSORS;
    }


    Serial.println();

    Serial.println(
        "DS18B20"
    );

    Serial.print(
        "Sondes : "
    );

    Serial.println(
        sensorCount
    );


    // === RECUPERATION ADRESSES
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
            Serial.print(
                "S"
            );

            Serial.print(
                i + 1
            );

            Serial.print(
                " adresse : "
            );

            printSensorAddress(
                sensorAddresses[i]
            );

            Serial.println();
        }
        else
        {
            Serial.print(
                "ERREUR adresse S"
            );

            Serial.println(
                i + 1
            );
        }
    }


    // === RESOLUTION
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


    // === CONVERSION NON BLOQUANTE
    sensors.setWaitForConversion(
        false
    );


    // === INITIALISATION TEMPERATURES
    for (
        uint8_t i = 0;
        i < MAX_SENSORS;
        i++
    )
    {
        temperatures[i] =
            DEVICE_DISCONNECTED_C;
    }


    // === PREMIERE MESURE IMMEDIATE
    lastMeasurement =
        millis() -
        MEASUREMENT_INTERVAL;
}


// === LANCER CONVERSION
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


    Serial.println(
        "CONVERSION START"
    );
}


// === TERMINER CONVERSION
void finishTemperatureConversion()
{
    if (
        !conversionRunning
    )
    {
        return;
    }


    // === ATTENTE CONVERSION
    if (
        millis() -
        conversionStart <
        CONVERSION_TIME_MS
    )
    {
        return;
    }


    // === LECTURE SONDES
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


        // === TEMPERATURE VALIDE
        if (
            temperature !=
            DEVICE_DISCONNECTED_C
        )
        {
            temperatures[i] =
                temperature;
        }


        Serial.print(
            "S"
        );

        Serial.print(
            i + 1
        );

        Serial.print(
            " : "
        );


        // === ERREUR LECTURE
        if (
            temperature ==
            DEVICE_DISCONNECTED_C
        )
        {
            Serial.println(
                "ERREUR DECONNEXION"
            );
        }


        // === TEMPERATURE
        else
        {
            Serial.println(
                temperature,
                2
            );
        }
    }


    conversionRunning =
        false;

    lastMeasurement =
        millis();


    Serial.println(
        "CONVERSION END"
    );
}


// === LECTURE TEMPERATURES
void readTemperatures()
{
    // === CONVERSION EN COURS
    if (
        conversionRunning
    )
    {
        finishTemperatureConversion();

        return;
    }


    // === ATTENTE INTERVALLE
    if (
        millis() -
        lastMeasurement <
        MEASUREMENT_INTERVAL
    )
    {
        return;
    }


    // === NOUVELLE CONVERSION
    startTemperatureConversion();
}