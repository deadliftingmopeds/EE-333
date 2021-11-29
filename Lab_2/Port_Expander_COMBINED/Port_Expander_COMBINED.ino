#include <Wire.h>
#include <SPI.h>


#define CHIP_SELECT 10

void setup() {

  pinMode(CHIP_SELECT, OUTPUT);
  Wire.begin();
  SPI.begin();

  Wire.beginTransmission(32);
  Wire.write(byte(0x00));   
  Wire.write(byte(0x00));
  Wire.endTransmission();

  digitalWrite(CHIP_SELECT, LOW);  //
  SPI.transfer(0x40);
  SPI.transfer(0x00);   //
  SPI.transfer(0x00);     //
  digitalWrite(CHIP_SELECT, HIGH);  //  
}


byte val = 0;

void loop() {
  
  Wire.beginTransmission(32);	//
  Wire.write(byte(0x09));	// address of GPIO register
  Wire.write(val);		// 
  Wire.endTransmission();

  digitalWrite(CHIP_SELECT, LOW);  
  SPI.transfer(0x40);
  SPI.transfer(0x09);  
  SPI.transfer(val);     
  digitalWrite(CHIP_SELECT, HIGH);  
  
  val++;				
  if (val == 256) 
    val = 0;
  
  delay(100);
}
