#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "config.h"

void temperatureInit();

void readTemperatures();

void startTemperatureConversion();

void finishTemperatureConversion();

extern float temperatures[MAX_SENSORS];

extern uint8_t sensorCount;

extern DeviceAddress sensorAddresses[MAX_SENSORS];

#endif