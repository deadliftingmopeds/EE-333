/* BCD conversion functions based on information gathered from link below
 * https://stackoverflow.com/questions/28133020/how-to-convert-bcd-to-decimal
 */


#include <LiquidCrystal.h>
#include <Wire.h>

const int rs = 8, en = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  lcd.begin(16, 2);
  lcd.print("RTC Demo");

//  Wire.beginTransmission(0x68);  // start transmission
//  Wire.write(0x00);              // set start address
//  Wire.write(0x00);              // 0-3 sec, 4-6 10 sec
//  Wire.write(0x42);              // 0-3 min and 4-6 10 min
//  Wire.write(0x50);              // 0-3 hour, 4 10 hour, 5 10 hour && (~AM/PM), 6 (12/~24)
//  Wire.write(0x06);              // 0-2 day (1-7)
//  Wire.write(0x29);              // 0-3 date , 4-5 10 date
//  Wire.write(0x91);              // 0-3 month, 4 10 month, 7 century  
//  Wire.write(0x21);              // 0-3 year, 4-7 10 year
//  Wire.endTransmission();        // stop transmitting
//
//  delay(500);

}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(0x68);
  Wire.write(0);              // sends start adress 00h
  Wire.endTransmission();     // stop transmitting

  Wire.requestFrom(0x68, 7);    // request 7 bytes from the RTC

  if(Wire.available() == 7)       // slave may send less than requested
  { 
    byte seconds = Wire.read();    // receive a byte as character
    byte minutes = Wire.read();    // receive a byte as character
    byte hours   = Wire.read();    // receive a byte as character
    byte day     = Wire.read();    // receive a byte as character
    byte date    = Wire.read();    // receive a byte as character
    byte month   = Wire.read();    // receive a byte as character
    byte year    = Wire.read();    // receive a byte as character
      lcd.setCursor(0,0);
      lcd.print("Date: ");
      lcd.print((month & 0x10)>>4);  // mask month byte for xxx1_xxxx and shift four places
      lcd.print(month & 0x0F);       // mask month byte for xxxx_1111
      lcd.print("/");
      lcd.print((date & 0x30)>>4);   // mask month byte for xx11_xxxx and shift four places
      lcd.print(date & 0x0F);        // mask month byte for xxxx_1111 
      lcd.print("/");
      lcd.print((year & 0xF0)>>4);
      lcd.print(year & 0x0F);
      lcd.setCursor(0,1);
      lcd.print("Time: ");
      if(hours & 0x40){                  // If we are in 12hr time 
        lcd.print((hours & 0x10)>>4); // print only the last 5 bits
        lcd.print(hours & 0x0F);      // 
      }
      else{                              // If we are in 24hr time
        lcd.print((hours & 0x30)>>4); // print the last 6  
        lcd.print(hours & 0x0F);      //
      }
      lcd.print(":");
      lcd.print((minutes & 0x70)>>4);
      lcd.print(minutes & 0x0F);
      lcd.print(":");  
      lcd.print((seconds & 0x70)>>4);
      lcd.print(seconds & 0x0F);
      if(hours & 0x40){                  // If we are in 12hr time
        if(hours & 0x20)                 // and the PM bit is asserted
        lcd.print("PM ");             // print "PM"
        else                             // otherwise
        lcd.print("AM ");             // print "AM"
      }
   }
  delay(1000);
}
