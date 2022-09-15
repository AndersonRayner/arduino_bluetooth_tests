#include <Arduino.h>

// Bluetooth on Serial 5
// Basically echos whatever you type over the bluetooth connection
// and toggles and LED when you read something.


void printSomething();

void setup()
{

  // Set up Serial ports
  Serial.begin(115200);
  Serial5.begin(57600); 

  // Set up LEDs
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);

}

void loop()
{

  // Now just opening as a serial bridge
  while (Serial.available())
  {
    Serial5.write(Serial.read());
  }

  while (Serial5.available())
  {
    Serial.write(Serial5.read());
    digitalWrite(5,!digitalRead(5));
  }

  printSomething();

}

void printSomething()
{
  static uint32_t t_last = millis();

  if ((millis() - t_last) < 3UL*1000) return;

  t_last = millis();

  Serial5.printf("t: %.2f\n",t_last/1000.0f);
  digitalWrite(4,!digitalRead(4));

  return;


}
