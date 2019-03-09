const int LED_RED = 11;
const int LED_GREEN = 10;
const int LED_BLUE = 9;
const int TOGGLE = 8;
const int SENSOR = A0;

int high = 0;
int low = 0;
bool calibrated = false;

void setup() {
  pinMode(LED_RED,OUTPUT);
  pinMode(LED_GREEN,OUTPUT);
  pinMode(LED_BLUE,OUTPUT);
  pinMode(SENSOR,INPUT);
  pinMode(TOGGLE,INPUT);
  Serial.begin(9600);
  Serial.println("Communication established");
  analogWrite(LED_RED,125);
  delay(500);
  analogWrite(LED_RED,254);
  delay(500);
  analogWrite(LED_BLUE,125);
  delay(500);
  analogWrite(LED_BLUE,254);
  delay(500);
  analogWrite(LED_GREEN,125);
  delay(500);
  analogWrite(LED_GREEN,254);
  delay(500);
  analogWrite(LED_GREEN,0);
  analogWrite(LED_RED,0);
  analogWrite(LED_BLUE,0);
  Serial.print("Test Complete");
}

const int RED = 0;
const int GREEN = 1;
const int BLUE = 2;
const int RED_GREEN = 3;
const int RED_BLUE = 4;
const int BLUE_GREEN = 5;
const int WHITE = 6;

int mode = RED;
bool pressedPrev = false;

void loop() {
  bool toggleState = digitalRead(TOGGLE) == HIGH;
  
  if(!pressedPrev && toggleState){
    if(calibrated){
      mode = nextMode(mode);
    }else{
      calibrateLight();
    }
  }

  if(calibrated){
    setLED(getBrightness(),mode);
  }
  pressedPrev = toggleState;
}

int nextMode(int current){
  switch(current){
    case RED:
      return GREEN;
      break;
    case GREEN:
      return BLUE;
      break;
    case BLUE:
      return RED_GREEN;
      break;
    case RED_GREEN:
      return RED_BLUE;
      break;
    case RED_BLUE:
      return BLUE_GREEN;
      break;
    case BLUE_GREEN:
      return WHITE;
      break;  
    case WHITE:
      return RED;
      break;  
    default:
      Serial.println("FATAL ERROR HAS OCCURED");
      while(true);
      break;
  }
  return 0;
}

void setLED(int brightness, int mode){
  int red = 0;
  int blue = 0;
  int green = 0;
  if(mode == RED 
      || mode == RED_GREEN 
      || mode == RED_BLUE
      || mode == WHITE){
    red = brightness;
  }

  if(mode == GREEN 
      || mode == RED_GREEN 
      || mode == BLUE_GREEN
      || mode == WHITE){
    green = brightness;
  }

  if(mode == BLUE 
      || mode == BLUE_GREEN 
      || mode == RED_BLUE
      || mode == WHITE){
    blue = brightness;
  }

  analogWrite(LED_RED,red);
  analogWrite(LED_GREEN,green);
  analogWrite(LED_BLUE,blue);
}

const int calibrationTime = 5000;

void calibrateLight(){
  Serial.println("Starting Calibration");
  Serial.println("Calculating Low");

  unsigned long start = millis();
  low = analogRead(SENSOR);
  for(unsigned long i = start;
      i < start + calibrationTime;
      i = millis()){
    int reading = analogRead(SENSOR);
    if(reading < low){
      low = reading;
    }
  }
  
  Serial.println("Calculating High");
  high = analogRead(SENSOR);
  start = millis();
  for(unsigned long i = start;
      i < start + calibrationTime;
      i = millis()){
    int reading = analogRead(SENSOR);
    if(reading > high){
      high = reading;
    }
  }

  Serial.print("High: ");
  Serial.print(high);
  Serial.print(" Low: ");
  Serial.println(low);
  if(high <= low){
    high = low+1;
  }
  calibrated = true;
}

bool lock = true;

int getBrightness(){
  int reading = analogRead(SENSOR);
  if(reading - low < 0){
    return 0;
  }else{
    
    if(lock){
      Serial.println(((reading - low) / ((high - low) * 1.0)) * 255.0);
      Serial.println(low);
      Serial.println(high);
      Serial.println(reading);
      lock = false;
    }
    
    return ((reading - low) / ((high - low) * 1.0)) * 255.0;
  }
}
