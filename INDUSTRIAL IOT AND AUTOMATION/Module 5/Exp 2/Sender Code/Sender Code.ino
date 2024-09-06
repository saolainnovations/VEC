#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

// ThingSpeak API details
String apiKey = "Your_Write_API_Key";  // Write API Key
const char* server = "http://api.thingspeak.com";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Connect to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Simulate sensor data (or replace with actual sensor readings)
    float sensorValue = random(0, 100);  // Simulated sensor value

    // Prepare the URL with the data to send
    String url = String(server) + "/update?api_key=" + apiKey + "&field1=" + String(sensorValue);

    // Send the HTTP GET request to ThingSpeak
    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("Data sent to ThingSpeak, response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error sending data: ");
      Serial.println(httpResponseCode);
    }

    http.end();  // Close the connection
  }

  // Send data every 20 seconds
  delay(20000);
}
