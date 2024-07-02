#define samp_siz 4 
#define rise_threshold 5 
#define SerialMon             Serial
#define SerialAT              Serial1

#include <WiFi.h>   // Include the WiFi library
#include <HTTPClient.h>  // Include the HTTPClient library

const char* ssid = "HUAWEI Y6";     // Replace with your WiFi network SSID
const char* password = "123456789"; // Replace with your WiFi network password

const char server[] = "https://c5xbm0fj-5000.uks1.devtunnels.ms/"; // Replace with your server address

const int heart_pin = 14;  // Define the analog pin connected to the heart rate sensor
const int numReadings = 10; // Number of readings to average
int readings[numReadings];  // Array to store the sensor readings
int readIndex = 0;          // Current index of the readings array
int total = 0;              // Total of the readings array
int average = 0;            // Average of the readings
int sensorPin = 0; 
String id = "user";

WiFiClient client;  // Create a WiFi client object

void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password); // Connect to WiFi network

  while (WiFi.status() != WL_CONNECTED) { // Wait for connection
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
}

int read_heart_rate()
{
  SerialMon.println("Starting to read heart rate...");
  float reads[samp_siz], sum; 
    long int now, ptr; 
    float last, reader, start; 
    float first, second, third, before, print_value; 
    bool rising; 
    int rise_count; 
    int n; 
    long int last_beat; 
    for (int i = 0; i < samp_siz; i++) 
      reads[i] = 0; 
    sum = 0; 
    ptr = 0; 
      // calculate an average of the sensor 
      // during a 20 ms period (this will eliminate 
      // the 50 Hz noise caused by electric light 
      n = 0; 
      start = millis(); 
      reader = 0.; 
      do 
      { 
        reader += analogRead (sensorPin); 
        n++; 
        now = millis(); 
      } 
      while (now < start + 20);   
      reader /= n;  // we got an average 
      // Add the newest measurement to an array 
      // and subtract the oldest measurement from the array 
      // to maintain a sum of last measurements 
      sum -= reads[ptr]; 
      sum += reader; 
      reads[ptr] = reader; 
      last = sum / samp_siz; 
      // now last holds the average of the values in the array 
      // check for a rising curve (= a heart beat) 
      if (last > before) 
      { 
        rise_count++; 
        if (!rising && rise_count > rise_threshold) 
        { 
          // Ok, we have detected a rising curve, which implies a heartbeat. 
          // Record the time since last beat, keep track of the two previous 
          // times (first, second, third) to get a weighed average. 
          // The rising flag prevents us from detecting the same rise  
          // more than once. 
          rising = true; 
          first = millis() - last_beat; 
          last_beat = millis(); 
          // Calculate the weighed average of heartbeat rate 
          // according to the three last beats 
          print_value = 60000. / (0.4 * first + 0.3 * second + 0.3 * third); 
          Serial.print(print_value);
          // delay(5000);
          // sendToServer(print_value); 
          Serial.print('\n'); 
          third = second; 
          second = first; 
          return print_value;
        } 
      } 
      else 
      { 
        // Ok, the curve is falling 
        rising = false; 
        rise_count = 0; 
      } 
      before = last; 
      ptr++; 
      ptr %= samp_siz; 
}

void sendToServer() {
  if (WiFi.status() == WL_CONNECTED) {
        SerialMon.println("Performing HTTP POST request...");

        HTTPClient http;
        http.begin(server);

      // int value = read_heart_rate();
      int value = random(60, 100);

        // Define the JSON data to be sent
        String postData = "{\"id\": \"user\", \"heart_rate\":" + String(value) + "}";

        // Set content type to application/json
        http.addHeader("Content-Type", "application/json");

        // Send the request
        int httpResponseCode = http.POST(postData);

        // Check the response code
        SerialMon.print("HTTP Response code: ");
        SerialMon.println(httpResponseCode);

        // Free resources
        http.end();
    } else {
        Serial.println("Connecting to WiFi...");
        WiFi.begin(ssid, password); // Connect to WiFi network

        while (WiFi.status() != WL_CONNECTED) { // Wait for connection
          delay(1000);
          Serial.println("Connecting to WiFi...");
        }

        Serial.println("Connected to WiFi");
        Serial.println(WiFi.localIP());
    }
}

void setup() { 
    Serial.begin(9600); 
    delay(500);
    sendToServer();
} 
void loop () 
{ 
  // int heart_value = read_heart_rate();
  // delay(2000);
  // sendToServer(heart_value);
  sendToServer();
  delay(5000);
}