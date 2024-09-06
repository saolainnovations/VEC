#include <WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";

// ThingSpeak MQTT credentials
const char* mqttServer = "mqtt.thingspeak.com";
const int mqttPort = 1883;
const char* mqttUser = "your_mqtt_username";  // Can be your ThingSpeak MQTT Username (optional)
const char* mqttPassword = "your_mqtt_password"; // ThingSpeak API Write key as the password
const char* clientID = "ESP32Client";         // Client ID for MQTT (can be any unique string)

// ThingSpeak channel details
const char* channelID = "YOUR_CHANNEL_ID";
const char* writeAPIKey = "YOUR_API_KEY";

// Ultrasonic Sensor pins
const int trigPin = 5;   // GPIO 5
const int echoPin = 18;  // GPIO 18

WiFiClient espClient;
PubSubClient client(espClient);

long duration;
int distance;

void setup() {
  Serial.begin(115200);
  
  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Connect to Wi-Fi
  connectToWiFi();

  // Set up MQTT connection
  client.setServer(mqttServer, mqttPort);
}

void loop() {
  // Check Wi-Fi and MQTT connections
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  // Get distance from the ultrasonic sensor
  distance = getUltrasonicDistance();

  // Publish data to ThingSpeak via MQTT
  String payload = "field1=" + String(distance);
  String topic = "channels/" + String(channelID) + "/publish/" + writeAPIKey;

  // Publish to ThingSpeak
  if (client.publish(topic.c_str(), payload.c_str())) {
    Serial.println("Data published: " + payload);
  } else {
    Serial.println("Failed to publish data");
  }

  // Wait 20 seconds before sending the next update (ThingSpeak has a rate limit)
  delay(20000);
}

// Function to connect to Wi-Fi
void connectToWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

// Function to reconnect to MQTT if connection is lost
void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect(clientID, mqttUser, mqttPassword)) {
      Serial.println("Connected to MQTT");
    } else {
      Serial.print("Failed to connect to MQTT, state=");
      Serial.println(client.state());
      delay(5000);  // Retry every 5 seconds
    }
  }
}

// Function to get distance using the ultrasonic sensor
int getUltrasonicDistance() {
  // Send a 10µs pulse to the Trig pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the Echo pin
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}
