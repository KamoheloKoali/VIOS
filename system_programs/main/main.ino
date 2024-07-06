#include "main.h"

void setup() 
{
  // Set console baud rate
  Serial.begin(115200);
  delay(10);
    // make_call();
}

void loop()
{
    readHeartRate();
    // Serial.println("Heartbeat detected(from main loop): " + String(value));
}