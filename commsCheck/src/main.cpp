#include <Arduino.h>

// Bluetooth on Serial 1
// Basically echos whatever you type over the bluetooth connection
// and toggles and LED when you read something.

// You might have to configure the bluetooth module to operate at 57k baud


void printSomething();

void setup()
{

  // Set up Serial ports
  Serial.begin(115200);
  Serial1.begin(57600); 

  // Set up LEDs
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);

}

void loop()
{

  // Now just opening as a serial bridge
  while (Serial.available())
  {
    Serial1.write(Serial.read());
  }

  while (Serial1.available())
  {
    Serial.write(Serial1.read());
    digitalWrite(5,!digitalRead(5));
  }

  printSomething();

}

void printSomething()
{
  static uint32_t t_last = millis();

  if ((millis() - t_last) < 3UL*1000) return;

  t_last = millis();

  Serial1.printf("t: %.2f\n",t_last/1000.0f);
  Serial.printf("t: %.2f (Loopback)\n",t_last/1000.0f);
  digitalWrite(4,!digitalRead(4));

  return;


}
