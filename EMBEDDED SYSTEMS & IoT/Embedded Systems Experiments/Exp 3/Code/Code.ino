char characterToSend = 'A';  // The character to send

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud
}

void loop() {
  Serial.println(characterToSend);  // Send the character to HyperTerminal
  delay(1000);  // Wait for 1 second before sending the next character
}
