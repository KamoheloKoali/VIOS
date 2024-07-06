#define samp_siz 4
#define rise_threshold 4

#include <WiFi.h>              // Include the WiFi library
#include <HTTPClient.h>        // Include the HTTPClient library

// Pulse Monitor  Test Script
const int sensorPin = 35; // Define the analog pin connected to the heart rate sensor
const char* ssid = "HUAWEI Y6";     // Replace with your WiFi network SSID
const char* password = "123456789"; // Replace with your WiFi network password
const char server[] = "https://c5xbm0fj-5000.uks1.devtunnels.ms"; // Replace with your server address

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

void setup() {
    Serial.begin(115200); // Increased baud rate for faster serial communication
    delay(500);
    pinMode(sensorPin, INPUT);
    connectToWiFi();
    delay(700);
}

int readHeartRate() {
    float reads[samp_siz], sum;
    long int now, ptr;
    float last, reader, start;
    float first, second, third, before, print_value;
    bool rising = false;
    int rise_count = 0;
    int n;
    long int last_beat = 0;

    for (int i = 0; i < samp_siz; i++) {
        reads[i] = 0;
    }
    sum = 0;
    ptr = 0;

    Serial.println("Starting sensor reading loop...");

    while (true) {
        // Calculate an average of the sensor during a 20 ms period to eliminate noise
        n = 0;
        start = millis();
        reader = 0.0;
        do {
            reader += analogRead(sensorPin);
            n++;
            now = millis();
            // Serial.print("Now: ");
            // Serial.println(now);
        } while (now < start + 20);
        reader /= n;  // Calculate average

        // Add the newest measurement to an array and subtract the oldest measurement from the array to maintain a sum of last measurements
        sum -= reads[ptr];
        sum += reader;
        reads[ptr] = reader;
        last = sum / samp_siz;
        // Now last holds the average of the values in the array

        // Debug prints
        // Serial.print("Reader: ");
        // Serial.println(reader);
        // Serial.print("Sum: ");
        // Serial.println(sum);
        // Serial.print("Last: ");
        // Serial.println(last);

        // Check for a rising curve (i.e., a heartbeat)
        if (last > before) {
            rise_count++;
            if (!rising && rise_count > rise_threshold) {
                // Ok, we have detected a rising curve, which implies a heartbeat.
                // Record the time since last beat, keep track of the two previous times (first, second, third) to get a weighted average.
                // The rising flag prevents us from detecting the same rise more than once.
                rising = true;
                first = millis() - last_beat;
                last_beat = millis();

                // Calculate the weighted average of heartbeat rate according to the three last beats
                print_value = 60000. / (0.4 * first + 0.3 * second + 0.3 * third);

                Serial.print("Heartbeat detected: " + String(print_value));
                return print_value;

                third = second;
                second = first;
            }
        } else {
            // Ok, the curve is falling
            rising = false;
            rise_count = 0;
        }
        before = last;

        ptr++;
        ptr %= samp_siz;

        // Add a delay to avoid overwhelming the serial output
        delay(100);
        Serial.println("Finished readHeartRate");
        // return print_value;
    }
}

void loop() {
    int heart_rate_value = readHeartRate();  // Perform heart rate calculation
    delay(1000);
    sendToServer(heart_rate_value);
    delay(100);
}
