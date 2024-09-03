const int soilMoisturePin = 7;  // Pin where the soil moisture sensor is connected
int soilMoistureValue = 0;      // Variable to store the sensor value

void setup() {
  Serial.begin(9600);           // Initialize serial communication at 9600 baud rate
}

void loop() {
  soilMoistureValue = digitalRead(soilMoisturePin);  // Read the value from the sensor
  Serial.print("Soil Moisture Value: ");
  Serial.println(soilMoistureValue);                // Print the sensor value to the Serial Monitor

  delay(4000);                                      // Wait for 4 seconds before the next reading
}
