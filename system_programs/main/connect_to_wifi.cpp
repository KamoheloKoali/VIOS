#include "main.h"

const char* ssid = "HUAWEI Y6";     // Replace with your WiFi network SSID
const char* password = "123456789"; // Replace with your WiFi network password
bool wifiConnected = false;

void connectToWiFi() {
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password); // Connect to WiFi network

    unsigned long startAttemptTime = millis();

    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) { // Wait for connection
        delay(100);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        wifiConnected = true;
        Serial.println("Connected to WiFi");
        Serial.println(WiFi.localIP());
    } else {
        wifiConnected = false;
        Serial.println("Failed to connect to WiFi");
    }
}

void disconnectWiFi() {
    if (WiFi.status() == WL_CONNECTED) {
        WiFi.disconnect();
        wifiConnected = false;
        Serial.println("Disconnected from WiFi");
    } else {
        Serial.println("WiFi is already disconnected");
    }
}