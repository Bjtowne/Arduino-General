#include <SoftwareSerial.h>
const int BT_TX = 9;
const int BT_RX = 8;
const int BAUD = 9600;
SoftwareSerial BTSerial(BT_RX,BT_TX);

const int FIRST_LED = 6;
const int SECOND_LED = 7;
const int MOTOR_A_EN = 5;
const int MOTOR_A[] = {4,3};
const int MOTOR_B_EN = 10;
const int MOTOR_B[] = {11,12};

const int CMD_ALL_STOP = 0;
const int CMD_FIRST_LED_ON = 1;
const int CMD_FIRST_LED_OFF = 2;
const int CMD_SECOND_LED_ON = 3;
const int CMD_SECOND_LED_OFF = 4;
const int CMD_FORWARD_SLOW = 5;
const int CMD_FORWARD_MEDIUM = 6;
const int CMD_FORWARD_FAST = 7;
const int CMD_BACKWARDS_SLOW = 8;
const int CMD_BACKWARDS_MEDIUM = 9;
const int CMD_BACKWARDS_FAST = 10;
const int CMD_LEFT_SLOW = 11;
const int CMD_LEFT_MEDIUM = 12;
const int CMD_LEFT_FAST = 13;
const int CMD_RIGHT_SLOW = 14;
const int CMD_RIGHT_MEDIUM = 15;
const int CMD_RIGHT_FAST = 16;

const boolean debug = true;

void setup() {
  Serial.begin(BAUD);
  debugMsg("Communication Established");
  BTSerial.begin(BAUD);
  
  pinMode(FIRST_LED,OUTPUT);
  pinMode(SECOND_LED,OUTPUT);
  pinMode(MOTOR_A_EN,OUTPUT);
  pinMode(MOTOR_A[0],OUTPUT);
  pinMode(MOTOR_A[1],OUTPUT);
  pinMode(MOTOR_B_EN,OUTPUT);
  pinMode(MOTOR_B[0],OUTPUT);
  pinMode(MOTOR_B[1],OUTPUT);

  digitalWrite(FIRST_LED,LOW);
  digitalWrite(SECOND_LED,LOW);
  digitalWrite(MOTOR_A_EN,LOW);
  digitalWrite(MOTOR_A[0],LOW);
  digitalWrite(MOTOR_A[1],HIGH);
  digitalWrite(MOTOR_B_EN,LOW);
  digitalWrite(MOTOR_B[0],LOW);
  digitalWrite(MOTOR_B[1],HIGH);

}

void loop() {
  if(BTSerial.available()){
    byte cmd = BTSerial.read();
    debugMsg("TESTING" + cmd);
    //String output = "Command recieved: (" + cmd;
    //output = output + ") ";
    //output = output + getCommand(cmd);
    //debugMsg(output);
    switch(cmd){
        case CMD_ALL_STOP:
          motorsEn(false);
          break;
        case CMD_FIRST_LED_ON:
          digitalWrite(FIRST_LED,HIGH);
          motorsEn(true);
          break;
        case CMD_FIRST_LED_OFF:
          motorsEn(false);
          digitalWrite(FIRST_LED,LOW);
          break;
        case CMD_SECOND_LED_ON:
          digitalWrite(SECOND_LED,HIGH);
          break;
        case CMD_SECOND_LED_OFF:
          digitalWrite(SECOND_LED,LOW);
          break;
        case CMD_FORWARD_SLOW:
        case CMD_FORWARD_MEDIUM:
        case CMD_FORWARD_FAST:
          motorsEn(true);
          motorClockwise(MOTOR_A,true);
          motorClockwise(MOTOR_B,false);
          break;
        case CMD_BACKWARDS_SLOW:
        case CMD_BACKWARDS_MEDIUM:
        case CMD_BACKWARDS_FAST:
          motorsEn(true);
          motorClockwise(MOTOR_A,false);
          motorClockwise(MOTOR_B,true);
          break;
        case CMD_LEFT_SLOW:
        case CMD_LEFT_MEDIUM:
        case CMD_LEFT_FAST:
          motorsEn(true);
          motorClockwise(MOTOR_A,false);
          motorClockwise(MOTOR_B,false);
          break;
        case CMD_RIGHT_SLOW:
        case CMD_RIGHT_MEDIUM:
        case CMD_RIGHT_FAST:
          motorsEn(true);
          motorClockwise(MOTOR_A,true);
          motorClockwise(MOTOR_B,true);
          break;
    }
  }
}

String getCommand(int cmd){
  switch(cmd){
        case CMD_ALL_STOP:
          return "CMD_ALL_STOP";
        case CMD_FIRST_LED_ON:
          return "CMD_FIRST_LED_ON";
        case CMD_FIRST_LED_OFF:
          return "CMD_FIRST_LED_OFF";
        case CMD_SECOND_LED_ON:
          return "CMD_SECOND_LED_ON";
        case CMD_SECOND_LED_OFF:
          return "CMD_SECOND_LED_OFF";
        case CMD_FORWARD_SLOW:
          return "CMD_FORWARD_SLOW";
        case CMD_FORWARD_MEDIUM:
          return "CMD_FORWARD_MEDIUM";
        case CMD_FORWARD_FAST:
          return "CMD_FORWARD_FAST";
        case CMD_BACKWARDS_SLOW:
          return "CMD_BACKWARDS_SLOW";
        case CMD_BACKWARDS_MEDIUM:
          return "CMD_BACKWARDS_MEDIUM";
        case CMD_BACKWARDS_FAST:
          return "CMD_BACKWARDS_FAST";
        case CMD_LEFT_SLOW:
          return "CMD_LEFT_SLOW";
        case CMD_LEFT_MEDIUM:
          return "CMD_LEFT_MEDIUM";
        case CMD_LEFT_FAST:
          return "CMD_LEFT_FAST";
        case CMD_RIGHT_SLOW:
          return "CMD_RIGHT_SLOW";
        case CMD_RIGHT_MEDIUM:
          return "CMD_RIGHT_MEDIUM";
        case CMD_RIGHT_FAST:
          return "CMD_RIGHT_FAST";
        default:
          return "UNKNOWN";
    }
}

void debugMsg(String message){
  if(debug){
    Serial.println(message);
  }
}

void motorsEn(boolean en){
    if(en){
      digitalWrite(MOTOR_A_EN,HIGH);
      digitalWrite(MOTOR_B_EN,HIGH);
    }else{
      digitalWrite(MOTOR_A_EN,LOW);
      digitalWrite(MOTOR_B_EN,LOW);
    }
}

void motorClockwise(const int motor[], boolean dir){
  if(dir){
    digitalWrite(motor[0],HIGH);
    digitalWrite(motor[1],LOW);
  }else{
    digitalWrite(motor[0],LOW);
    digitalWrite(motor[1],HIGH);
  }
}
