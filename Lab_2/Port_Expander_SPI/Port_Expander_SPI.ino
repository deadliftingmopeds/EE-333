#include <SPI.h>


// SPI Port Expander sketch

#define CHIP_SELECT 10

void setup() {

  pinMode(CHIP_SELECT, OUTPUT);     // Sets pin 10 to output 
  digitalWrite(CHIP_SELECT, HIGH);  // Pulls CS high
  SPI.begin();                      // Configures MISO, MOSI 
                                    // and CLK starting SPI connection
 
  digitalWrite(CHIP_SELECT, LOW); 	// Pulls CS low
  SPI.transfer(0x40);               // SPI Address 0100_0000 = 0x40
  SPI.transfer(0x00);		            // 00h IODIR register
  SPI.transfer(0x00); 		          // sets all pins as output
  digitalWrite(CHIP_SELECT, HIGH);	// Pulls CS high
    
}

byte val = 0;

void loop() {

  digitalWrite(CHIP_SELECT, LOW);   // Pulls CS low
  SPI.transfer(0x40);               // SPI Address 0100_0000 = 0x40
  SPI.transfer(0x09);               // address of GPIO register
  SPI.transfer(val);                // sends byte 
  digitalWrite(CHIP_SELECT, HIGH);  // Pulls CS high
  val++;				
  if (val == 256) {
    val = 0;
  }
  
  delay(500);
}
