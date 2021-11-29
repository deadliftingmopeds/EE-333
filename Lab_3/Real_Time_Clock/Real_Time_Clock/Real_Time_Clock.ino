/*
 Real Time Clock Demonstration
 Allan Douglas
 Oregon Tech, 2017
 */

#include <Wire.h>
void setup() {
  byte sec = 0;
  
  Wire.begin();
  Serial.begin(9600);
  Serial.println("RTC Demonstration");

//// Comment out after time has been set and reupload  
//  
//  Wire.beginTransmission(0x68);  // start transmission
//  Wire.write(0x00);              // set start address
//  Wire.write(0x00);              // 0-3 sec, 4-6 10 sec
//  Wire.write(0x42);              // 0-3 min and 4-6 10 min
//  Wire.write(0x70);              // 0-3 hour, 4 10 hour, 5 10 hour & (~AM/PM), 6 (12/~24)
//  Wire.write(0x06);              // 0-2 day (1-7)
//  Wire.write(0x29);              // 0-3 date , 4-5 10 date
//  Wire.write(0x11);              // 0-3 month, 4 10 month, 7 century  
//  Wire.write(0x21);              // 0-3 year, 4-7 10 year
//  Wire.endTransmission();        // stop transmitting
}

void loop() {
  Wire.beginTransmission(0x68);
  Wire.write(0);              // sends value byte  
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

    // Print date to serial port
    Serial.print("Date: ");
    Serial.print((month & 0x10)>>4);  // mask month byte for xxx1_xxxx and shift four places
    Serial.print(month & 0x0F);       // mask month byte for xxxx_1111
    Serial.print("/");
    Serial.print((date & 0x30)>>4);   // mask month byte for xx11_xxxx and shift four places
    Serial.print(date & 0x0F);        // mask month byte for xxxx_1111 
    Serial.print("/");
    Serial.print((year & 0xF0)>>4);
    Serial.print(year & 0x0F);

    // Print time to serial port
    Serial.print(" Time: ");
    if(hours & 0x40){                  // If we are in 12hr time 
      Serial.print((hours & 0x10)>>4); // print only the last 5 bits
      Serial.print(hours & 0x0F);      // 
    }
    else{                              // If we are in 24hr time
      Serial.print((hours & 0x30)>>4); // print the last 6  
      Serial.print(hours & 0x0F);      //
    }
    Serial.print(":");
    Serial.print((minutes & 0x70)>>4);
    Serial.print(minutes & 0x0F);
    Serial.print(":");  
    Serial.print((seconds & 0x70)>>4);
    Serial.print(seconds & 0x0F);
    if(hours & 0x40){                  // If we are in 12hr time
      if(hours & 0x20)                 // and the PM bit is asserted
      Serial.print("PM ");             // print "PM"
      else                             // otherwise
      Serial.print("AM ");             // print "AM"
    }
    Serial.println(" ");
  }

  delay(1000);
}
