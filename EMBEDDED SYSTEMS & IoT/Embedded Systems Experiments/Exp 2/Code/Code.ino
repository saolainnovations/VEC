int pwmPin = 9;  // PWM pin (9, 10, 11, or 3)

void setup() {
  Serial.begin(9600); // Start the serial communication at 9600 baud rate
  pinMode(pwmPin, OUTPUT); // Set the pin as an output
}

void loop() {
  int pwmValue = 128; // 50% duty cycle (0 to 255 range)

  // Generate the PWM signal
  analogWrite(pwmPin, pwmValue);

  // Plot the PWM signal on the Serial Plotter
  if (millis() % 1000 < 500) {
    Serial.println(255);  // High state
  } else {
    Serial.println(0);    // Low state
  }

  delay(10); // Add a small delay to control the update rate on the plotter
}
