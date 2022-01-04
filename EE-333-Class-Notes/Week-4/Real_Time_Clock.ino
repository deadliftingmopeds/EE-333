/*
 Real Time Clock Demonstration
 Allan Douglas
 Oregon Tech, 2017
 */

#include <Wire.h>

void setup() {

  Wire.begin();
  Serial.begin(9600);
  Serial.println("RTC Demonstration");

  Wire.beginTransmission(0x68);
  Wire.write(0);              // set the address
  Wire.endTransmission();     // stop transmitting

  Wire.requestFrom(0x68,1);   // read one byte
  if(Wire.available == 1)
    byte sec = Wire.read();   // read a byte from the buffer

  Wire.beginTransmission(0x68);
  Wire.write(0);              // set the address
  Wire.write(sec & 0x7F);     // clear CH bit
  Wire.endTransmission();     // stop transmitting
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
    Serial.print((month & 0x10)>>4);
    Serial.print(month & 0x0F);
    Serial.print("/");
    Serial.print((date & 0x70)>>4);
    Serial.print(date & 0x0F);
    Serial.print("/");
    Serial.print((year & 0x70)>>4);
    Serial.print(year & 0x0F);

    // Print time to serial port
    Serial.print(" Time: ");
    Serial.print(hours);
    Serial.print(":");
    Serial.print((minutes & 0x70)>>4);
    Serial.print(minutes & 0x0F);
    Serial.print(":");  
    Serial.print((seconds & 0x70)>>4);
    Serial.print(seconds & 0x0F);
    Serial.println("");
  }

  delay(1000);
}

