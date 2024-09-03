#include <SoftwareSerial.h>

// Define the HC-12 serial pins
SoftwareSerial HC12(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);       // Serial monitor communication
  HC12.begin(9600);         // HC-12 communication
  
  Serial.println("HC-12 Transmitter Ready");
  Serial.println("Type your message and press Enter to send:");
}

void loop() {
  if (Serial.available()) {
    String dataToSend = Serial.readStringUntil('\n'); // Read input from Serial Monitor until newline
    
    HC12.println(dataToSend); // Send the data to the receiver
    
    Serial.println("Sent: " + dataToSend); // Print to Serial monitor
  }
}
