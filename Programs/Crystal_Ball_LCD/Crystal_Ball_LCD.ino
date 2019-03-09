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
  Serial.write(2);
  lcd.begin(16,2);
  pinMode(BUTTON,INPUT); 
  lcd.blink();
  lcd.cursor();
}

bool buttonState;
bool prevButtonState = false;
int reply = 0;

void loop() {
  buttonState = digitalRead(BUTTON);
  if(buttonState && !prevButtonState){
  }
  String input = Serial.readString();
  if(input.length() >= 1){
    printString(input);
  }
  
}

int col = 0;
int row = 0;

void printString(String out){
  unsigned int chars = out.length();
  chars--;
  for(unsigned int i = 0;i < chars;i++){
    printChar(out.charAt(i));
  }
}

void printChar(char out){
  if(col >= 16){
    col = 0;
    if(row == 1){
      row = 0;
      lcd.setCursor(0,0);
    }else{
      row = 1;
      lcd.setCursor(0,1);
    }
  }
  lcd.print(out);
  col++;
}
