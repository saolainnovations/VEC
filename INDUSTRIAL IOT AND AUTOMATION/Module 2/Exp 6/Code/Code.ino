#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "your_wifi_ssid";        // Your WiFi SSID
const char* password = "your_wifi_password"; // Your WiFi password

const char* apiKey = "YOUR_API_KEY";        // ThingSpeak Write API key
const char* server = "http://api.thingspeak.com/update";

int magneticSwitchPin = D6; // D6 pin 
int magneticSwitchState = 0;

void setup() {
  Serial.begin(115200);
  pinMode(magneticSwitchPin, INPUT_PULLUP);  // Initialize magnetic switch pin as input with pull-up

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Read the magnetic switch state
  magneticSwitchState = digitalRead(magneticSwitchPin);

  // Send data to ThingSpeak via HTTP POST
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Prepare the URL with the API key and field data
    String url = String(server) + "?api_key=" + apiKey + "&field7=" + String(magneticSwitchState);

    http.begin(url);  // Start the connection to the server
    int httpResponseCode = http.GET();  // Send the HTTP GET request

    // Check the response
    if (httpResponseCode > 0) {
      Serial.println("Data sent successfully. HTTP Response code: " + String(httpResponseCode));
    } else {
      Serial.println("Error sending data. HTTP Response code: " + String(httpResponseCode));
    }

    http.end();  // End the connection
  } else {
    Serial.println("WiFi not connected");
  }

  delay(20000);  // Wait for 20 seconds before sending the next update
}
