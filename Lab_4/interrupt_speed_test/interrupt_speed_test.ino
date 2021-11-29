/*
 * EEE-333 Lab 4 part 1: 
 * Written by Jared Rice 
 */

volatile unsigned long count = 0;
volatile unsigned long prev_count = 0;
int int_pin = 2;

void setup(){
  cli();                        // disable all interrupts
  pinMode(int_pin, INPUT);
  Serial.begin(115200);
  increment_count();
 // attachInterrupt(digitalPinToInterrupt(int_pin), increment_count, RISING); 
  sei();                       // enable all interrupts
}

void loop(){
  if(count > prev_count){
    Serial.println(count);
    
    prev_count = count;
  }
}
// Interrupt Service Routine
void increment_count(){
  count++;
}
