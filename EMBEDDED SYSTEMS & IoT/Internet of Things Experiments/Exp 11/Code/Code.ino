const int trigPin = 5;  // GPIO connected to Trig pin of the ultrasonic sensor
const int echoPin = 18; // GPIO connected to Echo pin of the ultrasonic sensor

void setup() {
  Serial.begin(115200);        // Start serial communication at 115200 baud rate
  pinMode(trigPin, OUTPUT);    // Set the trigPin as an output
  pinMode(echoPin, INPUT);     // Set the echoPin as an input
}

void loop() {
  long duration;
  float distance;
  
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Trigger the sensor by setting the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance (in centimeters)
  distance = duration * 0.034 / 2;
  
  // Print the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(1000); // Wait 1 second before the next measurement
}
