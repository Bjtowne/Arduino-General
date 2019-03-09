#include<LiquidCrystal.h>

const int LCD_RS = 12;
const int LCD_E = 11;
const int LCD_D4 = 5;
const int LCD_D5 = 4;
const int LCD_D6 = 3;
const int LCD_D7 = 2;
const int BUTTON = 6;

LiquidCrystal lcd(LCD_RS,LCD_E,LCD_D4,LCD_D5,LCD_D6,LCD_D7);

void setup() {
  Serial.begin(9600); 
  lcd.begin(16,2);
  pinMode(BUTTON,INPUT);
  printOut("Ask the");
  lcd.setCursor(0,1);
  printOut("Crystal Ball");
}

bool buttonState;
bool prevButtonState = false;
int reply = 0;

void loop() {
  
  buttonState = digitalRead(BUTTON) == HIGH;

  if(buttonState && !prevButtonState){
    if(reply >= 8){
      reply = 0;
    }else{
      reply++;
    }
    lcd.clear();
    lcd.setCursor(0,0);
    printOut("The ball says");
    lcd.setCursor(0,1);
    String output;
    switch(reply){
      case 0:
        output = "Yes";
        break;
      case 1:
        output = "Most likely";
        break;
      case 2:
        output = "Certainly";
        break;
      case 3:
        output = "Outlook good";
        break;
      case 4:
        output = "Unsure";
        break;
      case 5:
        output = "Ask again";
        break;
      case 6:
        output = "Doubtful";
        break;
      case 7:
        output = "No";
        break;
    }
    printOut(output);
  }
  prevButtonState = buttonState;
}

void printOut(String out){
  lcd.print(out);
  Serial.println(out);
}
