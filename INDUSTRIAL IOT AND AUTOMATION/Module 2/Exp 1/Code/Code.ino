#include <WiFi.h>
#include <HTTPClient.h>

// WiFi credentials
const char* ssid = "your_wifi_ssid";  // Replace with your WiFi SSID
const char* password = "your_wifi_password";  // Replace with your WiFi password

// ThingSpeak credentials
const char* server = "http://api.thingspeak.com";
String apiKey = "your_thingspeak_write_api_key";  // Replace with your ThingSpeak Write API Key
int channelID = your_channel_id;  // Replace with your ThingSpeak Channel ID

// Analog pins for sensors
const int mq3Pin = D33;  // MQ-3 connected to D33
const int mq4Pin = D32;  // MQ-4 connected to D32

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Read analog values from MQ-3 and MQ-4
  int mq3Value = analogRead(mq3Pin);
  int mq4Value = analogRead(mq4Pin);
  
  Serial.print("MQ-3 Value: ");
  Serial.println(mq3Value);
  
  Serial.print("MQ-4 Value: ");
  Serial.println(mq4Value);

  // Send data to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = server + "/update?api_key=" + apiKey + "&field1=" + String(mq3Value) + "&field2=" + String(mq4Value);
    http.begin(url);
    
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      Serial.println("Data sent to ThingSpeak");
      String response = http.getString();
      Serial.println(response);
    } else {
      Serial.println("Error in sending data to ThingSpeak");
    }
    
    http.end();
  }
  
  delay(20000);  // Wait for 20 seconds before sending the next data
}
