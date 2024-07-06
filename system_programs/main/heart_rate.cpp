#define samp_siz 4
#define rise_threshold 4
#include "main.h"

// Pulse Monitor  Test Script
const int sensorPin = 35; // Define the analog pin connected to the heart rate sensor

// void setup() {
//     Serial.begin(115200); // Increased baud rate for faster serial communication
//     delay(500);
//     pinMode(sensorPin, INPUT);
//     connectToWiFi();
//     delay(700);
// }

void readHeartRate() {
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

                Serial.println("Heartbeat detected: " + String(print_value));
                // return print_value;

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

// void loop() {
//     int heart_rate_value = readHeartRate();  // Perform heart rate calculation
//     delay(1000);
//     sendToServer(heart_rate_value);
//     delay(100);
// }
