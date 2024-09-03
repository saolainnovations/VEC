#include "DHT11.h"

#define DHT11_PIN 2 // Pin where the data pin of the DHT11 is connected

DHT11 dht(DHT11_PIN); // Create an instance of DHT11

void setup() {
  Serial.begin(9600); // Start the serial communication at 9600 baud rate
}

void loop() {
  int temperatureC = dht.readTemperature(); // Read temperature in Celsius
  int humidity = dht.readHumidity();       // Read humidity

  // Convert temperature from Celsius to Fahrenheit
  float temperatureF = temperatureC * 9.0 / 5.0 + 32.0;

  // Check if there is an error in reading temperature or humidity
  if (temperatureC == DHT11::ERROR_TIMEOUT || temperatureC == DHT11::ERROR_CHECKSUM) {
    Serial.print("Error reading temperature: ");
    Serial.println(DHT11::getErrorString(temperatureC));
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.print(" *C / ");
    Serial.print(temperatureF);
    Serial.println(" *F");
  }

  if (humidity == DHT11::ERROR_TIMEOUT || humidity == DHT11::ERROR_CHECKSUM) {
    Serial.print("Error reading humidity: ");
    Serial.println(DHT11::getErrorString(humidity));
  } else {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  delay(2000); // Wait for 2 seconds before the next reading
}
