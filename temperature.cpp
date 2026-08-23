#include "temperature.h"

#include <OneWire.h>
#include <DallasTemperature.h>

#include "defines.h"

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

float temperatures[MAX_SENSORS];

uint8_t sensorCount=0;


void temperatureInit()
{
    sensors.begin();

    sensorCount=sensors.getDeviceCount();

    if(sensorCount>MAX_SENSORS)
        sensorCount=MAX_SENSORS;

    Serial.println();
    Serial.println("DS18B20");

    Serial.print("Sondes : ");
    Serial.println(sensorCount);
}


void readTemperatures()
{
    sensors.requestTemperatures();

    for(uint8_t i=0;i<sensorCount;i++)
    {
        temperatures[i]=sensors.getTempCByIndex(i);

        Serial.print("S");
        Serial.print(i+1);
        Serial.print(" : ");
        Serial.println(temperatures[i]);
    }
}
