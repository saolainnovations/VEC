String stringToSend = "Hello, SVEC!";  // The string to send

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud
}

void loop() {
  Serial.println(stringToSend);  // Send the string to HyperTerminal
  delay(1000);  // Wait for 1 second before sending the string again
}
