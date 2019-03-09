
void setup() {
  Serial.begin(9600);
  Serial.println("Connection Established");
}

int value = 0;

int TONE_ONE = 400;
int TONE_TWO = 600;
int TONE_THREE = 800;
int TONE_FOUR = 1000;

int ONE[2] = {4,20};
int TWO[2] = {450,550};
int THREE[2] = {900,999};
int FOUR[2] = {1000,1050};

void loop() {
  int value = analogRead(0);
  Serial.println(value);
  int newTone = 0;
  if(inRange(ONE,value)){
    newTone = TONE_ONE;
  }else if(inRange(TWO,value)){
    newTone = TONE_TWO;
  }else if(inRange(THREE,value)){
    newTone = TONE_THREE;
  }else if(inRange(FOUR,value)){
    newTone = TONE_FOUR;
  }

  if(newTone != 0){
    tone(8,newTone);
  }else{
    noTone(8);
  }
      
}

boolean inRange(int* range, int value){
  return (value > range[0] && value < range[1]);
}
