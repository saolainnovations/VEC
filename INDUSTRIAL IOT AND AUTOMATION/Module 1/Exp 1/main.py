import RPi.GPIO as GPIO
import time

# Define GPIO pins
TRIG = 23
ECHO = 24

# Set up GPIO mode
GPIO.setmode(GPIO.BCM)
GPIO.setup(TRIG, GPIO.OUT)
GPIO.setup(ECHO, GPIO.IN)

def measure_distance():
    # Ensure TRIG is low
    GPIO.output(TRIG, False)
    time.sleep(2)  # Allow sensor to settle

    # Send a 10us pulse to trigger the sensor
    GPIO.output(TRIG, True)
    time.sleep(0.00001)
    GPIO.output(TRIG, False)

    # Wait for the echo to start
    while GPIO.input(ECHO) == 0:
        pulse_start = time.time()

    # Wait for the echo to stop
    while GPIO.input(ECHO) == 1:
        pulse_end = time.time()

    # Calculate the pulse duration
    pulse_duration = pulse_end - pulse_start

    # Calculate the distance
    distance = pulse_duration * 17150  # Speed of sound is 34300 cm/s, divided by 2
    distance = round(distance, 2)  # Round to 2 decimal places

    return distance

try:
    while True:
        distance = measure_distance()
        print(f"Distance: {distance} cm")
        time.sleep(1)  # Wait for 1 second before the next measurement

except KeyboardInterrupt:
    print("Measurement stopped by user")
    GPIO.cleanup()
