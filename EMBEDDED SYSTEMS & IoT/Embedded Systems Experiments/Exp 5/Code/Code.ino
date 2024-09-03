void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud
  Serial.println("Full Duplex Communication Started."); // Initial message
}

void loop() {
  // Check if data is available to read from HyperTerminal
  if (Serial.available() > 0) {
    // Read the incoming data byte
    char incomingByte = Serial.read();

    // Echo the received byte back to HyperTerminal
    Serial.print("Received: ");
    Serial.println(incomingByte);

    // Optionally, you can add logic here to process the incoming data
    // For example, respond with a predefined message:
    if (incomingByte == 'A') {
      Serial.println("You sent 'A'");
    } else if (incomingByte == 'B') {
      Serial.println("You sent 'B'");
    } else {
      Serial.println("Unknown character received.");
    }
  }

  // Send a periodic message to HyperTerminal
  Serial.println("Sending periodic message...");
  delay(2000);  // Delay of 2 seconds before sending the next message
}
