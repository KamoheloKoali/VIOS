#include <TinyGsmClient.h>
#include <HTTPClient.h>
#include <SD.h>
#include <SPI.h>
#include <BluetoothA2DPSink.h>
#include <BluetoothA2DPSource.h>
#include <ArduinoJson.h>

// Define the serial connections
#define TINY_GSM_MODEM_SIM800
#define MODEM_RST 5
#define MODEM_PWRKEY 4
#define MODEM_POWER_ON 23
#define MODEM_TX 27
#define MODEM_RX 26
#define I2C_SDA 21
#define I2C_SCL 22

// Set serial for debug console (to Serial Monitor, default speed 115200)
#define SerialMon Serial

// Use the hardware serial for communication with the SIM800 module
HardwareSerial SerialAT(1); // Use UART1

// Define the GSM modem
TinyGsm modem(SerialAT);

// Your GPRS credentials, if any
const char apn[]  = "your-apn";
const char gprsUser[] = "";
const char gprsPass[] = "";

// Server URL
const char* serverUrl = "http://yourserver.com/upload";

// SD card pin
const int chipSelect = 5;

// File names
const char* inputFileName = "/input.wav";
const char* outputFileName = "/output.wav";
const char* recordedFileName = "/recorded.wav";

// Variable to store command from JSON response
String command;

// Create instances
TinyGsm modem(Serial1);
TinyGsmClient client(modem);
HTTPClient http;
BluetoothA2DPSink a2dp_sink;
BluetoothA2DPSource a2dp_source;

// Forward declaration of functions
bool sendAudioFile(const char* filename);
void playAudioFile(const char* filename);
void recordAudioFile(const char* filename);

// std::vector<char> readFile(const std::string& filename) {
//     std::ifstream file(filename, std::ios::binary);
//     if (!file) {
//         throw std::runtime_error("Could not open file: " + filename);
//     }
//     return std::vector<char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
// }

// // Callback function to write the received data to a vector
// size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
//     size_t totalSize = size * nmemb;
//     std::vector<char>* buffer = (std::vector<char>*)userp;
//     buffer->insert(buffer->end(), (char*)contents, (char*)contents + totalSize);
//     return totalSize;
// }

/**
 * recordAudioFile - records command from the user
 * @filename - where to save the recorded audio
 */

void recordAudioFile(const char* filename) {
    File file = SD.open(filename, FILE_WRITE);
    if (!file) {
        Serial.println("Failed to open file for recording");
        return;
    }

    // Buffer to store incoming audio data
    uint8_t data[512];
    size_t bytesRead;

    // Start Bluetooth A2DP Source to capture audio
    a2dp_source.start("ESP32_AudioSource");

    // Capture audio for a specified duration (e.g., 10 seconds)
    unsigned long startTime = millis();
    unsigned long duration = 10000; // 10 seconds

    while (millis() - startTime < duration) {
        bytesRead = a2dp_source.read_data(data, 512);
        if (bytesRead > 0) {
            file.write(data, bytesRead);
        }
    }

    a2dp_source.stop();
    file.close();
    Serial.println("Recording finished");
}

/**
 * con_to_sim - connects to sim card
 */

void con_to_sim() 
{
    // Set GSM module baud rate
    Serial1.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX);

    // Initialize the modem
    Serial.println("Initializing modem...");
    pinMode(MODEM_PWRKEY, OUTPUT);
    pinMode(MODEM_POWER_ON, OUTPUT);
    digitalWrite(MODEM_PWRKEY, HIGH);
    digitalWrite(MODEM_POWER_ON, HIGH);

    // Restart takes quite some time
    // To skip it, call init() instead of restart()
    modem.restart();

    // Unlock your SIM card with a PIN if needed
    // modem.simUnlock("1234");

    Serial.println("Waiting for network...");
    if (!modem.waitForNetwork()) {
        Serial.println("Network connection failed");
        return;
    }

    Serial.println("Connecting to network...");
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
        Serial.println("GPRS connection failed");
        return;
    }

    Serial.println("Connected to network");
}

/**
 * sendAudioFile - sends the audio file to the server
 * @filename - name of the file to send
 * returns - bool
 */

bool sendAudioFile(const char* filename) {
    File file = SD.open(filename, FILE_READ);
    if (!file) {
        Serial.println("Failed to open file for sending");
        return false;
    }

    // Create buffer for file data
    size_t fileSize = file.size();
    uint8_t* buffer = (uint8_t*)malloc(fileSize);
    file.read(buffer, fileSize);
    file.close();

    http.begin(client, serverUrl);
    http.addHeader("Content-Type", "audio/wav");

    // Send POST request
    int httpResponseCode = http.POST(buffer, fileSize);
    free(buffer);

    if (httpResponseCode > 0) {
        Serial.printf("HTTP Response code: %d\n", httpResponseCode);

        // Get the response payload
        WiFiClient* stream = http.getStreamPtr();
        String response = "";
        while (stream->available()) {
            response += char(stream->read());
        }

        // Parse JSON response
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, response);
        if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return false;
        }

        // Extract command value from JSON
        if (doc.containsKey("command")) {
            command = doc["command"].as<String>();
            Serial.print("Command: ");
            Serial.println(command);
        }

        // Save the audio file if present in response
        if (doc.containsKey("audio")) {
            File outputFile = SD.open(outputFileName, FILE_WRITE);
            if (outputFile) {
                size_t len = stream->available();
                while (len > 0) {
                    uint8_t buf[128];
                    size_t size = stream->readBytes(buf, ((len > 128) ? 128 : len));
                    outputFile.write(buf, size);
                    len = stream->available();
                }
                outputFile.close();
                Serial.println("Received and saved response audio file");

                // Play the received audio file via Bluetooth
                playAudioFile(outputFileName);
            } else {
                Serial.println("Failed to open output file");
            }
        }
    } else {
        Serial.printf("HTTP POST failed, error: %s\n", http.errorToString(httpResponseCode).c_str());
    }

    http.end();
    return (httpResponseCode > 0);
}

/**
 * send_command - sends a command from user to  server
 */

void send_command() {
// Create instances
TinyGsm modem(Serial1);
TinyGsmClient client(modem);
HTTPClient http;

con_to_sim()

 // Initialize SD card
    if (!SD.begin(chipSelect)) {
        Serial.println("Card Mount Failed");
        return;
    }

    // Initialize Bluetooth A2DP Sink
    a2dp_sink.start("ESP32_AudioSink");

    // Record audio from Bluetooth headset
    recordAudioFile(recordedFileName);

    // Send the recorded audio file to the server
    if (!sendAudioFile(recordedFileName)) {
        Serial.println("Failed to send recorded audio file");
    }

    // Disconnect
    modem.gprsDisconnect();
    Serial.println("GPRS disconnected");
}

/**
 * playAudioFile - plays audio file from server to user
 */

void playAudioFile(const char* filename) {
    File file = SD.open(filename);
    if (!file) {
        Serial.println("Failed to open file for playback");
        return;
    }

    // Initialize Bluetooth A2DP Sink
    a2dp_sink.start("ESP32_Audio");

    size_t bytesRead;
    uint8_t data[512];
    while ((bytesRead = file.read(data, 512)) > 0) {
        a2dp_sink.write_data(data, bytesRead);
    }

    file.close();
    Serial.println("Playback finished");
}


/**
 * make_call - transmits a call to specified number
 * @number - number to be called
 */

void make_call(String number) 
{
    // Set GSM module baud rate
  SerialAT.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(3000);

  // Restart the modem
  SerialMon.println("Initializing modem...");
  modem.restart();

  // Unlock your SIM card with a PIN if needed
  // modem.simUnlock("1234");

  // Check signal quality
  SerialMon.println("Checking signal quality...");
  SerialAT.println("AT+CSQ");
  delay(1000);
  while (SerialAT.available()) {
    SerialMon.write(SerialAT.read());
  }

  // Wait for network connection
  SerialMon.println("Waiting for network...");
  if (!modem.waitForNetwork()) {
    SerialMon.println("Failed to connect to network");
    while (true);
  }
  SerialMon.println("Network connected");

  // Initiate a call
  String number = number; 

  SerialMon.println("Calling " + number);
  modem.callNumber(number);

  delay(20000); // Call duration in milliseconds, adjust as needed

  // Hang up the call using AT command
  SerialMon.println("Ending call");
  SerialAT.println("ATH");
  delay(1000); // Wait for the command to be processed
  SerialMon.println("Call ended");
}

/**
 * setup - entry point
 */

void setup() {
  // Set console baud rate
  SerialMon.begin(115200);
  delay(10);
}

/**
 * forever loop
 */

void loop() {
  // Do nothing in loop
}
