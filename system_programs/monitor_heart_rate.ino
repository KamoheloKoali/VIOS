int heart_pin = A0;
int heart_value;
void setup()
{
  // put your setup code here, to run once:
pinMode(heart_pin,INPUT);
Serial.begin(115200);
}


void loop()
{
heart_value = analogRead(heart_pin);
Serial.println(heart_value);
delay(200);
  // put your main code here, to run repeatedly:


}

