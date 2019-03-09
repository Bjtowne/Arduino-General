const int SPEAKER = 8;
const int SENSOR = A0;
const int CALIBRATION_TIME = 3000;

const int SPEAKER_HIGH = 8000;
const int SPEAKER_LOW = 50;

int low;
int high;

void setup() {
  pinMode(SPEAKER, OUTPUT);
  pinMode(SENSOR, INPUT);
  Serial.println("Communication established");
  Serial.println("Calibrating Sensor");
  unsigned long start = millis();
  low = analogRead(SENSOR);
  high = low + 1;
  while(millis() < start + CALIBRATION_TIME){
    int reading = analogRead(SENSOR);
    if(reading > high){
      high = reading;
    }
    if(reading < low){
      low = reading;
    }
  }
  Serial.print("Calibration complete, High: ");
  Serial.print(high);
  Serial.print(", Low: ");
  Serial.println(low);
}

void loop() {
  tone(SPEAKER,map(analogRead(SENSOR),low,high,SPEAKER_LOW,SPEAKER_HIGH));
}
