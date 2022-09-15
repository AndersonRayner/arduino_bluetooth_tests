#include <Arduino.h>

// Bluetooth on Serial 1 and 2

const int pin_bluetooth1_enable = 27;
const int pin_bluetooth1_state = 25;

const int pin_bluetooth2_enable = 38;
const int pin_bluetooth2_state = 40;


// Commands available at https://s3-sa-east-1.amazonaws.com/robocore-lojavirtual/709/HC-05_ATCommandSet.pdf


void send_command(Stream&, String);
void set_master(Stream&);
void set_slave(Stream&);
void print_properties(Stream&);
void printStatePin();

void setup()
{

  // Set up Serial ports
  Serial.begin(115200);

  // Set up pins
  pinMode(pin_bluetooth1_enable, OUTPUT);
  pinMode(pin_bluetooth2_enable, OUTPUT);

  pinMode(pin_bluetooth1_state, INPUT);
  pinMode(pin_bluetooth2_state, INPUT);

  // Put modules into the correct mode
  digitalWrite(pin_bluetooth1_enable, HIGH);
  digitalWrite(pin_bluetooth2_enable, HIGH);

  delay(2000);

  Serial1.begin(57600);  //38400
  Serial2.begin(57600);

  // Send codes
  String cmd;

  print_properties(Serial1);
  print_properties(Serial2);

  // Set some things
  set_master(Serial1);
  set_slave(Serial2);


  // Put module back into normal mode, reset teh module, and set correct baud
  Serial.write("Automatic commands done.  Opening a serial bridge\n");
  digitalWrite(pin_bluetooth1_enable, LOW);
  digitalWrite(pin_bluetooth2_enable, LOW);

  cmd = "AT+RESET\r\n";
  send_command(Serial1,cmd);
  send_command(Serial2,cmd);

}

void loop()
{

  // Now just opening as a serial bridge
  while (Serial.available())
  {
    Serial1.write(Serial.read());
  }

  while (Serial2.available())
  {
    Serial.write(Serial2.read());
  }

  printStatePin();

  
}

void set_master(Stream &port)
{

  Serial.print("=============== SET MASTER ==================\n");
  Serial.print("=============================================\n");

  String cmd;
  cmd = "AT+ROLE=1\r\n"; send_command(port, cmd);     // Set master
  cmd = "AT+NAME=sensor\r\n"; send_command(port, cmd);
  cmd = "AT+UART=57600,0,0\r\n"; send_command(port, cmd);
  cmd = "AT+BIND=0022:06:011035\r\n"; send_command(port, cmd);

  return;

}

void set_slave(Stream &port)
{
  Serial.print("=============== SET SLAVE ==================\n");
  Serial.print("============================================\n");

  String cmd;
  cmd = "AT+ROLE=0\r\n"; send_command(port, cmd);     // Set master
  cmd = "AT+NAME=vehicle\r\n"; send_command(port, cmd);
  cmd = "AT+UART=57600,0,0\r\n"; send_command(port, cmd);
  cmd = "AT+BIND=0022:06:011159\r\n"; send_command(port, cmd);

  return;

}

void print_properties(Stream &port)
{
  // Prints propeties of a bluetooth module

  String cmd;
  Serial.print("=============== PROPERTIES ==================\n");
  cmd = "AT+NAME?\r\n";    send_command(port, cmd);
  cmd = "AT+ADDR?\r\n";    send_command(port, cmd);
  cmd = "AT+VERSION?\r\n"; send_command(port, cmd);
  cmd = "AT+ROLE?\r\n";    send_command(port, cmd);
  cmd = "AT+PSWD?\r\n";    send_command(port, cmd);
  cmd = "AT+BIND?\r\n";    send_command(port, cmd);
  cmd = "AT+STATE?\r\n";   send_command(port, cmd); 
  cmd = "AT+UART?\r\n";    send_command(port, cmd);
  Serial.print("=============================================\n");

  return;
}

void printStatePin()
{
  static uint32_t t_last = millis();

  if (millis()-t_last < 1000) return;

  t_last = millis();  
  Serial.printf("State 1: %d, ",digitalRead(pin_bluetooth1_state));
  Serial.printf("State 2: %d\n",digitalRead(pin_bluetooth2_state));

  return;
}


void send_command(Stream &port, String cmd)
{

  // Send the command
  port.write(cmd.c_str());

  Serial.write(cmd.c_str());
  Serial.write("----------------\n");


  delay(100);


  // Read what data we have
  while (port.available())
  {
    Serial.write(port.read());
  }

  Serial.write("\n");

}
