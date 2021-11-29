#include <LiquidCrystal.h>
#define PMW_PIN 9

const int rs = 8, en = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte duty_cycle = 127;
unsigned int int_buffer;
char input_buffer[8];
void setup() {
  
  lcd.begin(16,2);
  lcd.print("PWM Test: ");
  pinMode(PMW_PIN, OUTPUT);
  lcd.setCursor(0,1);
  Serial.begin(9600);
  analogWrite(PMW_PIN, duty_cycle);
}

void loop() {

  
  if(Serial.available() > 0){
    Serial.readBytes(input_buffer, sizeof(input_buffer));  // reads into buffer 
    int_buffer = atoi(input_buffer);                       // c std string to int
    memset(input_buffer,0,sizeof(input_buffer));           // memset clears buffer
    duty_cycle = map(int_buffer,1,100,0,255);              // maps duty cycle into 8bits
    Serial.println();
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("D.C.=");
    lcd.print(int_buffer);
    lcd.print("% ");
    lcd.setCursor(0,1);
    lcd.print(duty_cycle);
    lcd.print("/");
    lcd.print(255*sizeof(duty_cycle));
    analogWrite(PMW_PIN, duty_cycle);
  }

  
  
  delay(100);
}

//    duty_cycle_255 = map(Serial.parseInt(),1,100,0,255);
//    Serial.print(duty_cycle_255,DEC);
//    lcd.setCursor(10,1);
//    lcd.print("     ");
//    lcd.setCursor(10,1);
//    lcd.print(duty_cycle_255);
