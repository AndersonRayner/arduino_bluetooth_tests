#include <Arduino.h>

// Bluetooth on Serial 1
// Given I haven't connected the EN pin, you'll have to hold the 
// the boot button as you power it on.  It's working correctly if 
// you get a slow, 1 Hz flashing on the LEDs

// Commands available at https://s3-sa-east-1.amazonaws.com/robocore-lojavirtual/709/HC-05_ATCommandSet.pdf

void setup()
{

  // Set up Serial ports
  Serial.begin(115200);
  Serial1.begin(57600);  // 38400 is default baud

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
  }


}
