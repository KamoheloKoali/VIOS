#include <WiFi.h>              // Include the WiFi library
#include <HTTPClient.h>        // Include the HTTPClient library

// Set serial for debug console (to Serial Monitor, default speed 115200)
#define SerialMon Serial

void make_call(void);
void connectToWiFi(void);
void disconnectWiFi(void);
void readHeartRate(void);
// void pulse_num();