// Working directory /home/major-arcana/Desktop/EE-333/Lab\ 2


char data;

void setup() {
  // Enables UART at 9600 baud
  Serial.begin(9600); 
}

void loop() {
  if (Serial.available() ) {
  data = Serial.read();
  Serial.print(data);
  }
}
