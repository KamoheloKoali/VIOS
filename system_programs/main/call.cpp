#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>
#include "main.h"

// Define the serial connections
#define MODEM_RST 5
#define MODEM_PWRKEY 4
#define MODEM_POWER_ON 23
#define MODEM_TX 27
#define MODEM_RX 26
#define I2C_SDA 21
#define I2C_SCL 22

// Use the hardware serial for communication with the SIM800 module
HardwareSerial SerialAT(1); // Use UART1

// Define the GSM modem
TinyGsm modem(SerialAT);

void make_call() {
  // Set GSM module baud rate
  SerialAT.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(3000);

  // Power on the modem
  pinMode(MODEM_PWRKEY, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);

  // Turn on the modem power
  SerialMon.println("Powering on the modem...");
  digitalWrite(MODEM_POWER_ON, HIGH);
  delay(1000);

  // Toggle the PWRKEY to turn on the modem
  SerialMon.println("Toggling PWRKEY to turn on the modem...");
  digitalWrite(MODEM_PWRKEY, HIGH);
  delay(1000);
  digitalWrite(MODEM_PWRKEY, LOW);
  delay(3000);

  // Initialize the modem
  SerialMon.println("Initializing modem...");
  if (!modem.restart()) {
    SerialMon.println("Failed to restart modem");
    while (true); // Halt the program if modem restart fails
  }
  SerialMon.println("Modem initialized");

  // Send an AT command to check if the modem is responding
  SerialMon.println("Sending AT command to modem...");
  SerialAT.println("AT");
  delay(1000);
  while (SerialAT.available()) {
    SerialMon.write(SerialAT.read());
  }
  SerialMon.println();

  // Check if modem is responding to AT commands
  if (!modem.testAT()) {
    SerialMon.println("Failed to communicate with modem");
    while (true); // Halt the program if communication fails
  }
  SerialMon.println("Modem is responding");

  // Check signal quality
  SerialMon.println("Checking signal quality...");
  SerialAT.println("AT+CSQ");
  delay(1000);
  while (SerialAT.available()) {
    SerialMon.write(SerialAT.read());
  }
  SerialMon.println();
  
  // Wait for network connection
  SerialMon.println("Waiting for network...");
  if (!modem.waitForNetwork()) {
    SerialMon.println("Failed to connect to network");
    while (true); // Halt the program if network connection fails
  }
  SerialMon.println("Network connected");

  // Check network status
  SerialMon.println("Checking network status...");
  if (modem.isNetworkConnected()) {
    SerialMon.println("Network is connected");
  } else {
    SerialMon.println("Network is not connected");
  }

  // Check for SIM card presence
  SerialMon.println("Checking SIM card...");
  int simStatus = modem.getSimStatus();
  switch (simStatus) {
  case 0:
    SerialMon.println("SIM card is unknown");
    break;
  case 1:
    SerialMon.println("SIM card is not inserted");
    break;
  case 2:
    SerialMon.println("SIM card is PIN locked");
    break;
  case 3:
    SerialMon.println("SIM card is ready");
    break;
  case 4:
    SerialMon.println("SIM card is NOT ready");
    break;
  default:
    SerialMon.print("SIM card status unknown, status: ");
    SerialMon.println(simStatus);
    break;
}

// Halt the program if SIM card is not ready
// if (simStatus != 3) {
//   while (true);
// }

  // Initiate a call
  String number = "+26657789238"; // Replace with the number you want to call
  SerialMon.println("Calling " + number);
  if (modem.callNumber(number)) {
    SerialMon.println("Call initiated successfully");
  } else {
    SerialMon.println("Failed to initiate call");
    while (true); // Halt the program if call initiation fails
  }

  delay(60000); // Call duration in milliseconds, adjust as needed

  // Hang up the call using AT command
  SerialMon.println("Ending call");
  SerialAT.println("ATH");
  delay(1000); // Wait for the command to be processed
  SerialMon.println("Call ended");
}
