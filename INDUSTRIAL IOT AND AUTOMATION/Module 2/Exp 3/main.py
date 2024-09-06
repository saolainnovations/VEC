import RPi.GPIO as GPIO
import time
import requests

# Set up GPIO pins
GPIO.setmode(GPIO.BCM)
TRIG = 23  # Trigger pin
ECHO = 24  # Echo pin

GPIO.setup(TRIG, GPIO.OUT)
GPIO.setup(ECHO, GPIO.IN)

# ThingSpeak API details
THINGSPEAK_WRITE_API_KEY = "YOUR_API_KEY"
THINGSPEAK_URL = "https://api.thingspeak.com/update"

def get_distance():
    # Ensure Trigger is low initially
    GPIO.output(TRIG, False)
    time.sleep(2)

    # Send a short pulse to trigger
    GPIO.output(TRIG, True)
    time.sleep(0.00001)
    GPIO.output(TRIG, False)

    # Measure the duration of the Echo pin high
    while GPIO.input(ECHO) == 0:
        pulse_start = time.time()

    while GPIO.input(ECHO) == 1:
        pulse_end = time.time()

    pulse_duration = pulse_end - pulse_start

    # Calculate distance (34300 cm/s is the speed of sound in air)
    distance = pulse_duration * 17150
    distance = round(distance, 2)

    return distance

def send_to_thingspeak(distance):
    # Create a dictionary of parameters for ThingSpeak
    data = {
        'api_key': THINGSPEAK_WRITE_API_KEY,
        'field4': distance  # Field where you want to store the data
    }

    # Send a request to ThingSpeak
    response = requests.post(THINGSPEAK_URL, params=data)

    if response.status_code == 200:
        print(f"Data sent to ThingSpeak: {distance} cm")
    else:
        print(f"Failed to send data, HTTP status code: {response.status_code}")

try:
    while True:
        distance = get_distance()
        print(f"Measured Distance: {distance} cm")

        # Send distance data to ThingSpeak
        send_to_thingspeak(distance)

        # Wait 15 seconds before sending the next reading (as ThingSpeak has a rate limit)
        time.sleep(15)

except KeyboardInterrupt:
    print("Measurement stopped by user")
    GPIO.cleanup()
