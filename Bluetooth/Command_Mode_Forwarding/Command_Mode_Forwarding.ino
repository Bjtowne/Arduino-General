/**
 * Used to forward Serial data from the computer to the BTModule. Used to test and setup the BT module.
 */


#include <SoftwareSerial.h>

//Pin to transmit data from the Arduino to the BT Module
const int BT_TX = 12;

//Pim use to recieve data from the BT Module to to the Arduino.
const int BT_RX = 13; 

const int DATA_BAUD = 9600;
const int AT_BAUD = 9600;
boolean enabled = false;

SoftwareSerial BTSerial(8,9);

void setup() {
  Serial.begin(9600);
  BTSerial.begin(38400);
  Serial.println("Communication Established");
}

void loop() {
  if(BTSerial.available()){
    Serial.write(BTSerial.read());
  }

  if(Serial.available()){
    BTSerial.write(Serial.read());
  }
}
