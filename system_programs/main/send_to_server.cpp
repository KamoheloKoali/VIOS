#include "main.h"

const char server[] = "https://c5xbm0fj-5000.uks1.devtunnels.ms"; // Replace with your server address

void sendToServer(int value) {
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Performing HTTP POST request...");

        HTTPClient http;
        http.begin(server);

        String postData = "{\"id\": \"user\", \"heart_rate\":" + String(value) + "}";

        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.POST(postData);

        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        http.end();
 
    //     if (value < 60 || value > 100) {
    //       if (!modem.restart() && !modem.testAT())
    //       {
    //           if (WiFi.status() == WL_CONNECTED) {
    //               SerialMon.println("Performing HTTP POST request...");

    //               HTTPClient http;
    //               http.begin(server1);

    //               String postData = "{\"res\": \"Failed to restart or communicate with modem\"}";

    //               http.addHeader("Content-Type", "application/json");

    //               int httpResponseCode = http.POST(postData);

    //               SerialMon.print("HTTP Response code: ");
    //               SerialMon.println(httpResponseCode);

    //               http.end();
    //           }
    //       }
    //       else 
    //       {
    //         make_call("+26656433164");
    //       }
    //     }
    // } else {
    //     connectToWiFi();
    // }
    }
}

