#include <SoftwareSerial.h>

//Pin to transmit data from the Arduino to the BT Module
const int BT_TX = 12;

//Pin use to recieve data from the BT Module to to the Arduino.
const int BT_RX = 13; 

const int BLUE_LED = 6;
const int RED_LED = 7;
const int MOTOR_A = 4;
const int MOTOR_B = 3;
const int MOTOR_CTRL = 5;

const int DATA_BAUD = 9600;
boolean enabled = false;

SoftwareSerial BTSerial(8,9);

void setup() {
  Serial.begin(9600);
  pinMode(BLUE_LED,OUTPUT);
  pinMode(RED_LED,OUTPUT);
  pinMode(MOTOR_A,OUTPUT);
  pinMode(MOTOR_B,OUTPUT);
  pinMode(MOTOR_CTRL,OUTPUT);

  digitalWrite(MOTOR_A,HIGH);
  digitalWrite(MOTOR_B,LOW);
  digitalWrite(MOTOR_CTRL,HIGH);
  
  BTSerial.begin(DATA_BAUD);
  Serial.println("Communication Established");
}

void loop() {
  if(BTSerial.available()){
    byte input = BTSerial.read();
    switch(input){
      case 1:
        Serial.println("1: Blue LED on");
        digitalWrite(BLUE_LED,HIGH);
        break;
      case 2:
        Serial.println("2: Blue LED off");
        digitalWrite(BLUE_LED,LOW);
        break;
      case 3:
        Serial.println("3: Red LED on");
        digitalWrite(RED_LED,HIGH);
        break;
      case 4:
        Serial.println("4: Red LED off");
        digitalWrite(RED_LED,LOW);
        break;
      case 5:
        Serial.println("5: Change motor direction");
        changeMotorDir();
        break;
      case 6:
        Serial.println("6: Turn motor on");
        digitalWrite(MOTOR_CTRL,HIGH);
        break;
      case 7:
        Serial.println("7: Turn motor off");
        digitalWrite(MOTOR_CTRL,LOW);
        break;
      default:
        Serial.println("Unknown communication received");
    }
  }
}

boolean dir = true;

void changeMotorDir(){
  if(dir){
    digitalWrite(MOTOR_A,HIGH);
    digitalWrite(MOTOR_B,LOW);
    dir = false;
  }else{
    digitalWrite(MOTOR_A,LOW);
    digitalWrite(MOTOR_B,HIGH);
    dir = true;
  }
}
