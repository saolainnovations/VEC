#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// ThingSpeak settings
const char* server = "http://api.thingspeak.com";
String apiKey = "your_API_KEY";

// Define the pin where the soil moisture sensor is connected
const int sensorPin = D2; // D2 pin

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi.");
}

void loop() {
  int sensorValue = digitalRead(sensorPin); // Read the digital value from the sensor
  Serial.print("Soil Moisture Status: ");
  Serial.println(sensorValue);

  if (WiFi.status() == WL_CONNECTED) {
    // Send data to ThingSpeak
    HTTPClient http;
    String url = server + "/update?api_key=" + apiKey + "&field5=" + String(sensorValue);
    
    http.begin(url);
    int httpCode = http.GET(); // Send the request

    // Check the HTTP status code
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Data sent to ThingSpeak: " + payload);
    } else {
      Serial.println("Error in sending data");
    }

    http.end(); // Close connection
  }

  delay(15000); // Wait for 15 seconds before sending the next data
}
