const int MOTOR_PIN = 9;
const int SWITCH_PIN = 2;

void setup() {
  pinMode(SWITCH_PIN,INPUT);
  pinMode(MOTOR_PIN,OUTPUT);
  Serial.begin(9600);
  Serial.println("Connection Established");
}



boolean prevSwitch = true;
boolean motorStatus = false;

void loop() {
  delay(10);
  boolean currentSwitch = (digitalRead(SWITCH_PIN) == HIGH);
  if(prevSwitch == LOW && currentSwitch == HIGH){
    motorStatus = !motorStatus;
    if(motorStatus){
      Serial.println("Button Pressed, motor status is now TRUE");
    }else{
      Serial.println("Button Pressed, motor status is now FALSE");
    }
    
    if(motorStatus){
      digitalWrite(MOTOR_PIN,HIGH);
    }else{
      digitalWrite(MOTOR_PIN,LOW);
    }
  }
  prevSwitch = currentSwitch;
}
