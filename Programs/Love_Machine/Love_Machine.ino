const int blueLED = 2;
const int greenLED = 3;
const int yellowLED = 4;
const int redLED = 5;
const int testLED = 13;
const int button = 6;
const int tempSensor = A0;

int lowTemp = 0;
int highTemp = 0;
int portionTemp = 0;
bool calibrated = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Communication open");
  pinMode(blueLED,OUTPUT);
  pinMode(redLED,OUTPUT);
  pinMode(yellowLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(button,INPUT);
  pinMode(tempSensor,INPUT);
  testLEDs();
}

void loop() {
  if(readCalibrateButton()){
    calibrate();
  }

  if(calibrated){
    int temp = readTemp();
    if(lowTemp + portionTemp > temp){
      setBlueLED(HIGH);
    }else{
      setBlueLED(LOW);
    }
    if(lowTemp + portionTemp * 2 > temp){
      setGreenLED(HIGH);
    }else{
      setGreenLED(LOW);
    }
    if(lowTemp + portionTemp * 3 > temp){
      setYellowLED(HIGH);
    }else{
      setYellowLED(LOW);
    }
    if(lowTemp + portionTemp * 4 > temp){
      setRedLED(HIGH);
    }else{
      setRedLED(LOW);
    }
    Serial.println(temp);
    
  }else{
    setLEDs(HIGH);
  }

}

//////////////////////////////////////////////////////////////////////
///////////////////// FUNCTIONS //////////////////////////////////////
//////////////////////////////////////////////////////////////////////

const unsigned int calibrateTime = 10000;

void calibrate(){
  Serial.println("Calibration has begun.");
  int low = readTemp();
  int high = readTemp();
  unsigned int start = millis();
  unsigned int portion = calibrateTime / 5;
  setLEDs(LOW);

  blinkLEDs(4);

  setBlueLED(HIGH);
  delay(1000);
  setBlueLED(LOW);

  //get low
  unsigned int currentTime = millis();
  start = currentTime;
  while(start + calibrateTime > millis()){
    if(currentTime > portion + start){
      setBlueLED(HIGH);
    }
    if(currentTime > portion * 2 + start){
      setGreenLED(HIGH);
    }
    if(currentTime > portion * 3 + start){
      setYellowLED(HIGH);
    }
    if(currentTime > portion * 4 + start){
      setRedLED(HIGH);
    }
    int current = readTemp();
    if(current > low){
      low = current;
    }
    currentTime = millis();
  }

  setLEDs(LOW);
  setRedLED(HIGH);
  delay(1000);
  setRedLED(LOW);

  //get high
  currentTime = millis();
  start = currentTime;
  while(start + calibrateTime > currentTime){
    if(currentTime > portion + start){
      setBlueLED(HIGH);
    }
    if(currentTime > portion * 2 + start){
      setGreenLED(HIGH);
    }
    if(currentTime > portion * 3 + start){
      setYellowLED(HIGH);
    }
    if(currentTime > portion * 4 + start){
      setRedLED(HIGH);
    }
    int current = readTemp();
    if(current > high){
      high = current;
    }
    currentTime = millis();
  }

  if(low > high){
    error();
  }

  blinkLEDs(4);

  lowTemp = low;
  highTemp = high;
  portionTemp = high-low / 4;
  
  calibrated = true;
  Serial.print("Calibration complete, High: ");
  Serial.print(high);
  Serial.print(", Low: ");
  Serial.println(low);
}

//////////////////////////////////////////////////////////////////////
///////////////////// DEVICE INTERFACE ///////////////////////////////
//////////////////////////////////////////////////////////////////////

const int blinkTime = 500;

void setRedLED(int setting){
  digitalWrite(redLED, setting);
}

void setGreenLED(int setting){
  digitalWrite(greenLED, setting);
}

void setYellowLED(int setting){
  digitalWrite(yellowLED, setting);
}

void setBlueLED(int setting){
  digitalWrite(blueLED, setting);
}

void setTestLED(int setting){
  digitalWrite(testLED, setting);
}

void blinkLEDs(int blinks){
  for(int i = 0;i < blinks;i++){
    setLEDs(HIGH);
    delay(blinkTime);
    setLEDs(LOW);
    delay(blinkTime);
  }
}

void setLEDs(int setting){
  setRedLED(setting);
  setGreenLED(setting);
  setYellowLED(setting);
  setBlueLED(setting);
}

int readTemp(){
  delay(100);
  return analogRead(tempSensor);
}

bool readCalibrateButton(){
  return digitalRead(button) == HIGH;
}

//////////////////////////////////////////////////////////////////////
///////////////////// DEVICE TESTS ///////////////////////////////////
//////////////////////////////////////////////////////////////////////

const int testDelay = 250;

void testLEDs(){
  setTestLED(HIGH);
  Serial.println("TEST LED TEST");
  delay(testDelay);
  setBlueLED(HIGH);
  Serial.println("BLUE LED TEST");
  delay(testDelay);
  setGreenLED(HIGH);
  Serial.println("GREEN LED TEST");
  delay(testDelay);
  setYellowLED(HIGH);
  Serial.println("YELLOW LED TEST");
  delay(testDelay);
  setRedLED(HIGH);
  Serial.println("RED LED TEST");
  delay(testDelay);
  setLEDs(LOW);
  setTestLED(LOW);
  delay(testDelay);
}

void error(){
  Serial.print("|||A FATAL ERROR HAS OCCURED|||");
  setLEDs(HIGH);
  while(true){
    setTestLED(HIGH);
    delay(testDelay);
    setTestLED(LOW);
    delay(testDelay);
  }
}
