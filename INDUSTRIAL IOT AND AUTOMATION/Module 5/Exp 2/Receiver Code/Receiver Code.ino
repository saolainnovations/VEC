#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

// ThingSpeak API details
String apiKey = "Your_Read_API_Key";  // Read API Key
String channelID = "Your_Channel_ID";  // Channel ID
const char* server = "http://api.thingspeak.com";

// Pin where you want to control an actuator (e.g., LED, relay, or buzzer)
const int actuatorPin = 2;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Setup the pin as output
  pinMode(actuatorPin, OUTPUT);

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

    // Prepare the URL to read data from ThingSpeak
    String url = String(server) + "/channels/" + channelID + "/fields/1.json?api_key=" + apiKey + "&results=1";

    // Send the HTTP GET request to ThingSpeak
    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.println("Received data from ThingSpeak:");
      Serial.println(payload);

      // Extract the field1 value from the JSON response
      int valueIndex = payload.indexOf("\"field1\":\"");
      if (valueIndex != -1) {
        String valueStr = payload.substring(valueIndex + 9, payload.indexOf("\"", valueIndex + 9));
        float receivedValue = valueStr.toFloat();

        // Actuate based on the received value
        if (receivedValue > 50) {  // Example condition
          digitalWrite(actuatorPin, HIGH);  // Turn on actuator
          Serial.println("Actuator ON");
        } else {
          digitalWrite(actuatorPin, LOW);  // Turn off actuator
          Serial.println("Actuator OFF");
        }
      }
    } else {
      Serial.print("Error receiving data: ");
      Serial.println(httpResponseCode);
    }

    http.end();  // Close the connection
  }

  // Read data every 20 seconds
  delay(20000);
}
