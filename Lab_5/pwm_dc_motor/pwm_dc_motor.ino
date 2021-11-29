#include <LiquidCrystal.h>
#define PMW_PIN 9

const int rs = 8, en = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int duty_cycle = 127;

void setup() {
  
  lcd.begin(16,2);
  lcd.print("PWM Test: ");
  pinMode(PMW_PIN, OUTPUT);
  lcd.setCursor(0,1);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  analogWrite(PMW_PIN, duty_cycle);
  lcd.setCursor(0,1);
  lcd.print("Duty Cycle=");
  lcd.print(map(duty_cycle,0,255,1,100));
}
