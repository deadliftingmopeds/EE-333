/*  Pulse Duration Timer
 *  Oregon Institute of Technology, 2015
 *   
 *  Allan A. Douglas
 */

volatile boolean update_flag;
volatile unsigned long startTime;
volatile unsigned long endTime;
int sensePin = 2;  // interrupt source

// interrupt service routine
void pulse() {
    if (digitalRead(sensePin)) {
      startTime = micros();
      update_flag = 0;
    }
    else {
      endTime = micros();
      update_flag = 1;
    }
}

void setup() {
  Serial.begin (115200);
  pinMode(sensePin, INPUT);
  attachInterrupt(digitalPinToInterrupt(sensePin), pulse, CHANGE);
  update_flag = 0;
} 

void loop() {
  if (update_flag) {
    Serial.println (long(endTime - startTime));    
    update_flag = 0;
  }
}
