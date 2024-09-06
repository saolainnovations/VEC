#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// ThingSpeak settings
String apiKey = "YOUR_API_KEY";  // Replace with your ThingSpeak Write API Key
const char* server = "http://api.thingspeak.com";

// Pin setup
const int switchPin = D5;  // D5 pin on the ESP32

// Variables to store switch state
int switchState = 0;

void setup() {
  Serial.begin(115200);
  
  // Initialize the switch pin as input
  pinMode(switchPin, INPUT_PULLUP);  // Use INPUT_PULLUP if you don't have a pull-up resistor
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("Connected to WiFi.");
}

void loop() {
  // Read the digital switch state
  switchState = digitalRead(switchPin);
  
  // Send data to ThingSpeak if switch state changes
  sendToThingSpeak(switchState);
  
  // Wait for a few seconds before sending the next reading
  delay(15000);  // ThingSpeak accepts data at 15-second intervals
}

void sendToThingSpeak(int state) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    // Prepare the URL to send data
    String url = server;
    url += "/update?api_key=" + apiKey;
    url += "&field6=" + String(state);
    
    http.begin(url);
    int httpCode = http.GET();  // Send the GET request
    
    if (httpCode > 0) {
      Serial.println("Data sent to ThingSpeak: " + String(state));
    } else {
      Serial.println("Error sending data to ThingSpeak");
    }
    
    http.end();  // Close connection
  } else {
    Serial.println("WiFi not connected");
  }
}
