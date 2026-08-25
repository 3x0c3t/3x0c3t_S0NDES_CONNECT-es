#ifndef BOOTSCREEN_H
#define BOOTSCREEN_H

void bootScreen();

void bootLedStatus(bool ok);
void bootBuzzerStatus(bool ok);
void bootWifiStatus(bool ok);
void bootIpAddress(const char* ip);

#endif
