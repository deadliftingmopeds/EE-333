#include <Wire.h>

// I2C Port Expander sketch

void setup() {
  Wire.begin(); 		// join I2C bus 
  

  Wire.beginTransmission(32);	// Slave address 0010_0000 = 32 = 0x20
  Wire.write(byte(0x00)); 	  // 00h IODIR register  
  Wire.write(byte(0x00));	    // sets all pins as output
  Wire.endTransmission();	    // sends bits queued in wire write
}

byte val = 0;

void loop() {
  Wire.beginTransmission(32);	//
  Wire.write(byte(0x09));	    // address of GPIO register
  Wire.write(val);		        // sends byte 
  Wire.endTransmission();	    //

  val++;		                 	// increments byte
  if (val == 256) {
    val = 0;
  }
  
  delay(500);
}
