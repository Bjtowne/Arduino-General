

void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,INPUT);
}

int const DELAY_TIME = 1000;
int currentPins = 0;
int const MAX_PIN = 8;

void loop() {
  delay(DELAY_TIME);
  int change;
  if(digitalRead(10) && currentPins < MAX_PIN){
    change = 1;
  }else if(!digitalRead(10) && currentPins > 0){
    change = -1;
  }else{
    change = 0;
  }
  currentPins += change;
  activePins(currentPins);
}

void activePins(int amount){
  for(int i = 0;i < MAX_PIN;i++){
    digitalWrite(i+2,LOW);
  }
  for(int i = 0;i < amount;i++){
    digitalWrite(i+2,HIGH);
  }
}
