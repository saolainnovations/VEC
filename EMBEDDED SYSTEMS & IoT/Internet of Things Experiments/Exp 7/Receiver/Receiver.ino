#include <SoftwareSerial.h>

// Define the HC-12 serial pins
SoftwareSerial HC12(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);       // Serial monitor communication
  HC12.begin(9600);         // HC-12 communication
  
  Serial.println("HC-12 Receiver Ready");
}

void loop() {
  if (HC12.available()) {
    String receivedData = HC12.readString(); // Read the incoming data
    
    Serial.println("Received: " + receivedData); // Print the received data to Serial monitor
  }
}
