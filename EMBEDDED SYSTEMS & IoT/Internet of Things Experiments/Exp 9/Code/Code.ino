const int ledPin = 2; // Define the pin connected to the LED

void setup() {
  pinMode(ledPin, OUTPUT);   // Set the LED pin as an output
  Serial.begin(9600);      // Start serial communication at 9600 baud rate
  Serial.println("Type 'on' to turn the LED on, 'off' to turn it off, or 'blink' to blink.");
}

void loop() {
  if (Serial.available()) {            // Check if data is available on the Serial Monitor
    String command = Serial.readStringUntil('\n'); // Read the input as a string until a newline
    
    command.trim();                    // Remove any extra white spaces

    if (command.equalsIgnoreCase("on")) {
      digitalWrite(ledPin, HIGH);       // Turn the LED on
      Serial.println("LED is ON");
    } 
    else if (command.equalsIgnoreCase("off")) {
      digitalWrite(ledPin, LOW);        // Turn the LED off
      Serial.println("LED is OFF");
    } 
    else if (command.equalsIgnoreCase("blink")) {
      Serial.println("LED is blinking...");
      for (int i = 0; i < 5; i++) {     // Blink the LED 5 times
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
      }
      Serial.println("LED stopped blinking.");
    } 
    else {
      Serial.println("Invalid command. Type 'on', 'off', or 'blink'.");
    }
  }
}
