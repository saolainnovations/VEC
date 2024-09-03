#include <Servo.h>

Servo myServo;  // Create a servo object

int servoPin = 9;  // PWM pin to control the servo

void setup() {
  myServo.attach(servoPin);  // Attach the servo on pin 9 to the servo object
}

void loop() {
  // Sweep from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);  // Set the servo to the current angle
    delay(15);  // Delay for smooth motion
  }
  
  delay(1000);  // Pause for 1 second

  // Sweep from 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);  // Set the servo to the current angle
    delay(15);  // Delay for smooth motion
  }
  
  delay(1000);  // Pause for 1 second
}
