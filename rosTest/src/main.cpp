#include <Arduino.h>


#define USE_TEENSY_HW_SERIAL
#include "ros.h"


#include "std_msgs/String.h"

// Bluetooth on Serial 5
// Given I haven't connected the EN pin, you'll have to hold the 
// the boot button as you power it on.  It's working correctly if 
// you get a slow, 1 Hz flashing on the LEDs

// Commands available at https://s3-sa-east-1.amazonaws.com/robocore-lojavirtual/709/HC-05_ATCommandSet.pdf

ros::NodeHandle nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello world!";


void setup()
{
  // Set up Pins
  pinMode(5,OUTPUT);
  digitalWrite(5,HIGH);

  // Set up Serial ports
  Serial.begin(115200);
  Serial1.begin(57600);  // Bluetooth serial port (38400 is default baud, changed this)

  // Set up ROS stuff
  nh.initNode();
  nh.advertise(chatter);

}

void loop()
{

  // Now just opening as a serial bridge
  digitalWrite(5,!digitalRead(5));
  str_msg.data = hello;
  chatter.publish( &str_msg );

  Serial.printf("%.2f : Message sent",(float) millis()/1000.0f);
  nh.spinOnce();
  delay(1000);


}
