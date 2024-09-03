const int xPin = A0;  // X-axis output to analog pin A0
const int yPin = A1;  // Y-axis output to analog pin A1
const int zPin = A2;  // Z-axis output to analog pin A2

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud
  Serial.println("ADXL335 Accelerometer Readings:");
}

void loop() {
  // Read the analog values from the accelerometer
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);
  int zValue = analogRead(zPin);

  // Convert the analog readings to voltage (assuming 5V reference)
  float xVoltage = (xValue / 1023.0) * 5.0;
  float yVoltage = (yValue / 1023.0) * 5.0;
  float zVoltage = (zValue / 1023.0) * 5.0;

  // Display the readings on the serial monitor/HyperTerminal
  Serial.print("X Voltage: ");
  Serial.print(xVoltage, 2);
  Serial.print(" V, Y Voltage: ");
  Serial.print(yVoltage, 2);
  Serial.print(" V, Z Voltage: ");
  Serial.println(zVoltage, 2);
  
  // Small delay before the next reading
  delay(500);
}
