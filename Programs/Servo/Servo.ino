const int SERVO = 9;
const int ACTUATOR = A0;

const int SERVO_MIN = 1;
const int ACTUATOR_MAX = 1023;
const int SERVO_MAX = 253;

void setup() {
  pinMode(SERVO,OUTPUT);
  pinMode(ACTUATOR,INPUT);
  Serial.begin(9600);
  Serial.println("Connection established");
  analogWrite(SERVO,0);
  delay(1000);
  analogWrite(SERVO,180);
  delay(1000);
  analogWrite(SERVO,90);
  delay(300);
  analogWrite(SERVO,180);
  delay(1000);
  analogWrite(SERVO,0);
  delay(1000);
}

int prevActuatorValue = analogRead(ACTUATOR);
int actuatorValue = prevActuatorValue;

void loop() {
  if(!withinRange(analogRead(ACTUATOR), actuatorValue, 5)){
    actuatorValue = analogRead(ACTUATOR);
  }
  if(!withinRange(actuatorValue, prevActuatorValue, 10)){
    Serial.print("Actuator: ");
    Serial.println(actuatorValue);
    prevActuatorValue = actuatorValue;
  }
  analogWrite(SERVO,map(actuatorValue,10,ACTUATOR_MAX,SERVO_MIN,SERVO_MAX));
  delay(100);
}

bool withinRange(int testValue, int primaryValue, int range){
  int upper = primaryValue + range;
  int lower = primaryValue - range;
  if(testValue >= lower && testValue <= upper){
    return true;
  }else{
    return false;
  }
}
