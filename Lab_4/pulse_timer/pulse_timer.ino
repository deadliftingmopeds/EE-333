/*  Pulse Duration Timer
    Oregon Institute of Technology, 2015

    Allan A. Douglas
*/

volatile boolean update_flag;
volatile unsigned long startTime;
volatile unsigned long endTime;
int sensePin = 2;  // interrupt source

// interrupt service routine
void pulse() {
  if (digitalRead(sensePin)) {                   // if sense pin is high
    startTime = micros();                        // record start time
    update_flag = 0;                             // set update flag to 0
  }
  else {                                         // if sense pin is low
    endTime = micros();                          // record end time
    update_flag = 1;                             // set update flag to 1
  }
}

void setup() {
  Serial.begin (500000);                         // start serial monitor
  pinMode(sensePin, INPUT);                      // set sense pin to output
  attachInterrupt(
    digitalPinToInterrupt(sensePin),             // attach interrupt, calling pulse()
    pulse, CHANGE);                              // when state change detected on pin2
    update_flag = 0;                             // sets update flag to 0
}                                                //

void loop() {
  if (update_flag) {                          // If update flag is 1,or pulse() has run once.
    Serial.println (long(endTime - startTime));   // Print the elapsed time between
                                                  // calls of pulse() and
    update_flag = 0;                              // reset update flag.
  }
}
