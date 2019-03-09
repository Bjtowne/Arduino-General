//The pin numbers for the input and output devices.
#define RED_LED 5
#define YELLOW_LED 4
#define GREEN_LED 3
#define BUTTON 7
#define TEST_LED 13

//List of different statuses that the program can take.
#define STATUS_GOOD 1
#define STATUS_BAD 2

//How long in milliseconds that the main loop is run.
#define LOOP_SPEED 100

//The amount of time in milliseconds before the next step of the test procedure
#define TEST_DELAY 250


//Current status of the program
int currentStatus = 0;

//The amount of times that the program has looped.
int loopCount = 0;

//If the button was pressed in the last program loop.
bool pressedPrev = false;


//Setup Arduino
void setup() {
  Serial.begin(9400);
  Serial.print("Communication open\n");
  pinMode(BUTTON,INPUT);
  pinMode(GREEN_LED,OUTPUT);
  pinMode(YELLOW_LED,OUTPUT);
  pinMode(RED_LED,OUTPUT);
  pinMode(TEST_LED,OUTPUT);
  digitalWrite(TEST_LED,LOW);
  currentStatus = STATUS_GOOD;
  testDevices();
}

//Main program loop
void loop() {
  if(getButton()){
    testLED(HIGH);
    //Serial.print("button: ");
    //Serial.print(getButton());
    //Serial.print(" previous: ");
    //Serial.print(pressedPrev);
    //Serial.print(" ");
  }else{
    testLED(LOW);
  }

  if(getButton() && pressedPrev){
    //Button Held
    currentStatus = STATUS_GOOD;
    testLED(HIGH);
  }else if(getButton() && !pressedPrev){
    //Button Pressed
    Serial.print("Pressed");
  }else if(!getButton() && pressedPrev){
    //Button Released
    Serial.print("Released");
  }else if (!getButton() && !pressedPrev){
    //Button Open
    currentStatus = STATUS_BAD;
    testLED(LOW);
  }else{
    error();
  }

  
  switch(currentStatus){
    case STATUS_GOOD:
      goodAction();
      break;
    case STATUS_BAD:
      badAction();
      break;
    default:
      error();
      break;
  }
  
  pressedPrev = getButton();
  loopCount++;
  delay(LOOP_SPEED);
}



//////////////////////////////////////////////////////////////////////
///////////////////// FUNCTIONAL METHODS /////////////////////////////
//////////////////////////////////////////////////////////////////////

//Action to take when the status is good.
void goodAction(){
  greenLED(HIGH);
  yellowLED(LOW);
  redLED(LOW);
}

//Action to take the status is bad.
void badAction(){
  greenLED(LOW);
  if(loopCount % 2 == 0){
    redLED(HIGH);
    yellowLED(LOW);
  }else{
    yellowLED(HIGH);
    redLED(LOW);
  }
}


//////////////////////////////////////////////////////////////////////
///////////////////// ASSISTANT METHODS //////////////////////////////
//////////////////////////////////////////////////////////////////////

//Update the setting of the Red LED.
void redLED(int setting){
  digitalWrite(RED_LED,setting);
}

//Update the setting of the Green LED.
void greenLED(int setting){
  digitalWrite(GREEN_LED,setting);
}

//Update the setting of the yellow LED.
void yellowLED(int setting){
  digitalWrite(YELLOW_LED,setting);
}

//Update the setting of the test LED
void testLED(int setting){
  digitalWrite(TEST_LED,setting);
}

bool getButton(){
  return digitalRead(BUTTON);
}

//////////////////////////////////////////////////////////////////////
///////////////////// TESTING METHODS ////////////////////////////////
//////////////////////////////////////////////////////////////////////

void error(){
  while(true){
    greenLED(HIGH);
    yellowLED(HIGH);
    redLED(HIGH);
    delay(TEST_DELAY);
    greenLED(LOW);
    yellowLED(LOW);
    redLED(LOW);
    delay(TEST_DELAY);
  }
}

void testDevices(){
  //LED Test
  ledScan(1);

  //Button Test
  if(getButton()){
    error();
  }

  while(!getButton()){
      redLED(LOW);
      greenLED(HIGH);
      delay(TEST_DELAY/2);
      redLED(HIGH);
      greenLED(LOW);
      delay(TEST_DELAY/2);
  }
  greenLED(LOW);
  redLED(LOW);

  //Device check complete
  for(int i = 0;i < 3;i++){
    ledScan(3);
  }
  delay(TEST_DELAY/3);
}

void ledScan(int timeFactor){
  testLED(HIGH);
  greenLED(LOW);
  yellowLED(LOW);
  redLED(LOW);
  delay(TEST_DELAY/timeFactor);
   testLED(LOW);
  greenLED(HIGH);
  yellowLED(LOW);
  redLED(LOW);
  delay(TEST_DELAY/timeFactor);
  testLED(LOW);
  greenLED(LOW);
  yellowLED(HIGH);
  redLED(LOW);
  delay(TEST_DELAY/timeFactor);
   testLED(LOW);
  greenLED(LOW);
  yellowLED(LOW);
  redLED(HIGH);
  delay(TEST_DELAY/timeFactor);
  redLED(LOW);
}
