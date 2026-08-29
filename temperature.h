#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "config.h"


// ============================================================
// INITIALISATION
// ============================================================

void temperatureInit();


// ============================================================
// LECTURE TEMPERATURES
// ============================================================

void readTemperatures();


// ============================================================
// CONVERSION
// ============================================================

void startTemperatureConversion();

void finishTemperatureConversion();


#endif