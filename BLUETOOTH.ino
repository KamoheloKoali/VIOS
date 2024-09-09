#define TINY_GSM_MODEM_SIM800
#include <BluetoothSerial.h>
#include <TinyGsmClient.h>
#include <BluetoothA2DPSource.h>

#define MODEM_RST 5
#define MODEM_PWRKEY 4
#define MODEM_POWER_ON 23
#define MODEM_TX 27
#define MODEM_RX 26

#define SerialMon Serial
#define TINY_GSM_MODEM_SIM800

BluetoothSerial SerialBT;
BluetoothA2DPSource a2dp_source;
HardwareSerial SerialAT(1);
TinyGsm modem(SerialAT);

const char *deviceName = "ESP32_A2DP_SOURCE1";
const String phoneNumber = "+26662659027"; // Replace with your phone number

void setup() {
  Serial.begin(115200);
  SerialAT.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX);

  pinMode(MODEM_PWRKEY, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);

  // Initialize GSM modem
  powerOnModem();
  initializeModem();

  // Initialize Bluetooth Serial
  if (!SerialBT.begin(deviceName)) {
    Serial.println("An error occurred initializing Bluetooth");
  } else {
    Serial.println("Bluetooth Serial started. Device is discoverable with name: " + String(deviceName));
  }

  // Initialize Bluetooth A2DP Source
  initializeBluetooth();

  // Initiate a call
  initiateCall(phoneNumber);

  delay(30000); // Duration of the call

  // End the call
  endCall();
}

void loop() {
  // Check Bluetooth connection status
  if (a2dp_source.is_connected()) {
    Serial.println("Bluetooth is connected and ready for audio streaming.");
  } else {
    Serial.println("Bluetooth is not connected.");
  }

  delay(100000); // Adjust delay as needed
}

void powerOnModem() {
  Serial.println("Powering on the modem...");
  digitalWrite(MODEM_POWER_ON, HIGH);
  delay(1000);
  Serial.println("Toggling PWRKEY to turn on the modem...");
  digitalWrite(MODEM_PWRKEY, HIGH);
  delay(1000);
  digitalWrite(MODEM_PWRKEY, LOW);
  delay(3000);
}

void initializeModem() {
  Serial.println("Initializing modem...");
  if (!modem.restart()) {
    Serial.println("Failed to restart modem");
    while (true);
  }
  Serial.println("Modem initialized");

  // Test AT command
  Serial.println("Sending AT command to modem...");
  SerialAT.println("AT");
  delay(1000);
  while (SerialAT.available()) {
    Serial.write(SerialAT.read());
  }
  Serial.println();

  if (!modem.testAT()) {
    Serial.println("Failed to communicate with modem");
    while (true);
  }
  Serial.println("Modem is responding");
}

void initiateCall(const String& number) {
  Serial.println("Initiating call to " + number);
  SerialAT.print("ATD");
  SerialAT.print(number);
  SerialAT.println(";");
  delay(5000); // Allow time for the call to initiate
}

void endCall() {
  Serial.println("Ending call");
  SerialAT.println("ATH");
  delay(1000); // Wait for the command to be processed
  Serial.println("Call ended");
}

void initializeBluetooth() {
  Serial.println("Initializing Bluetooth A2DP Source...");
  a2dp_source.start(deviceName);
  delay(5000); // Give time for Bluetooth initialization

  Serial.println("Waiting for Bluetooth connection...");
  unsigned long startMillis = millis();
  while (!a2dp_source.is_connected()) {
    delay(50000);
    Serial.println("Bluetooth is not connected.");
    if (millis() - startMillis > 30000) { // 30 seconds timeout
      Serial.println("Bluetooth connection timeout.");
      break;
    }
  }
  if (a2dp_source.is_connected()) {
    Serial.println("Bluetooth is connected and ready for audio streaming.");
  } else {
    Serial.println("Bluetooth failed to connect.");
  }
}

