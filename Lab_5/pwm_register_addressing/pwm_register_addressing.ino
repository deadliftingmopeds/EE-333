#include <LiquidCrystal.h>
#define PMW_PIN 9

const int rs = 8, en = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int duty_cycle = 127;

void setup() {
  
  lcd.begin(16,2);
  lcd.print("PWM Test: ");
  lcd.setCursor(0,1);
}
double t = 0;
void loop() {
  OCR1A = (unsigned int)(127.0 * sin(t*2.0*PI) + 128);
  delay(100);
  t = t + 0.1;
  lcd.setCursor(0,1);
  lcd.print(OCR1A);
}
