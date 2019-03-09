int const REVERSE_PIN = 12;
int const ACTIVE_PIN = 13;
int const ANALOG_INPUT = A0;
int const RED_LED = 11;
int const GREEN_LED = 10;
int const BRIDGE_A = 2;
int const BRIDGE_B = 3;
int const BRIDGE_EN = 9;

int const PWM_LOW = 0;
int const PWM_HIGH = 255;
int const ANALOG_LOW = 0;
int const ANALOG_HIGH = 1023;

void setup() {
  pinMode(REVERSE_PIN, INPUT);
  pinMode(ACTIVE_PIN, INPUT);
  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
  pinMode(BRIDGE_A,OUTPUT);
  pinMode(BRIDGE_B,OUTPUT);
  pinMode(ANALOG_INPUT,INPUT);
  pinMode(BRIDGE_EN,OUTPUT);
}

int const STATE_ON = 0;
int const STATE_COAST = 1;
int const STATE_BREAK = 2;

boolean prevReverse = true;
boolean prevActive = true;
boolean directionState = true;
int activeState = STATE_ON;
int frame = 0;

void loop() {
  boolean currReverse = digitalRead(REVERSE_PIN) == HIGH;
  boolean currActive = digitalRead(ACTIVE_PIN) == HIGH;
  if(!prevReverse && currReverse){
    directionState = !directionState;
  }
  if(!prevActive && currActive){
    switch(activeState){
      case STATE_ON:
      activeState = STATE_COAST;
      break;
      case STATE_COAST:
      activeState = STATE_BREAK;
      break;
      case STATE_BREAK:
      activeState = STATE_ON;
      break;
    }
  }
  switch(activeState){
    case STATE_ON:
      digitalWrite(RED_LED,LOW);
      digitalWrite(GREEN_LED,HIGH);
      analogWrite(BRIDGE_EN,map(analogRead(ANALOG_INPUT),ANALOG_LOW,ANALOG_HIGH,PWM_LOW,PWM_HIGH));
      if(directionState){
        digitalWrite(BRIDGE_A,HIGH);
        digitalWrite(BRIDGE_B,LOW);
      }else{
        digitalWrite(BRIDGE_A,LOW);
        digitalWrite(BRIDGE_B,HIGH);
      }
      break;
    
    case STATE_COAST:
      digitalWrite(RED_LED,LOW);
      digitalWrite(GREEN_LED,LOW);
      digitalWrite(BRIDGE_EN,LOW);
      break;
    
    case STATE_BREAK:
      digitalWrite(RED_LED,HIGH);
      digitalWrite(GREEN_LED,LOW);
      digitalWrite(BRIDGE_A,HIGH);
      digitalWrite(BRIDGE_B,HIGH);
      digitalWrite(BRIDGE_EN,HIGH);
      break;
  }

  prevReverse = currReverse;
  prevActive = currActive;
}
