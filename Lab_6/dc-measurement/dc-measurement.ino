#include <LiquidCrystal.h>

const int rs = 8, en = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){
  lcd.begin(16,2);
  lcd.print("Fuck");

  
}

void loop(){

  int analogSignal = analogRead(A0);
  //int analogSignal = map(analogRead(A0), 0, 255, 0, 10);
  lcd.setCursor(0,1);
  lcd.print("            ");
  lcd.setCursor(0,1);
  lcd.print(analogSignal);
  delay(100);
  //lcd.clear();
  //lcd.setCursor(0,0);
}
