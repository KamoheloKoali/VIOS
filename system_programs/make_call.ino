#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>

// Define the serial connections
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

void setup() {
  // Set console baud rate
  SerialMon.begin(115200);
  delay(10);

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
  String number = "+26663967055"; // Replace with the number you want to
call
  SerialMon.println("Calling " + number);
  modem.callNumber(number);

  delay(20000); // Call duration in milliseconds, adjust as needed

  // Hang up the call using AT command
  SerialMon.println("Ending call");
  SerialAT.println("ATH");
  delay(1000); // Wait for the command to be processed
  SerialMon.println("Call ended");
}

void loop() {
  // Do nothing in loop
}

