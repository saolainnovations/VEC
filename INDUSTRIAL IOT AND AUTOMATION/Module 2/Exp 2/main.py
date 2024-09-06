import RPi.GPIO as GPIO
import time
import requests

# GPIO setup
SENSOR_PIN = 17  # GPIO pin where the IR sensor is connected

# ThingSpeak Settings
THINGSPEAK_WRITE_API_KEY = "YOUR_THINGSPEAK_WRITE_API_KEY"  # Replace with your Write API Key
THINGSPEAK_URL = "https://api.thingspeak.com/update"

# Setup GPIO mode
GPIO.setmode(GPIO.BCM)
GPIO.setup(SENSOR_PIN, GPIO.IN)

def read_distance():
    # Read digital input from IR sensor
    if GPIO.input(SENSOR_PIN):
        return 1  # Object detected
    else:
        return 0  # No object detected

def send_data_to_thingspeak(distance):
    # Prepare the data to be sent to ThingSpeak
    payload = {
        'api_key': THINGSPEAK_WRITE_API_KEY,
        'field3': distance  # Sending data to field2
    }

    # Send data to ThingSpeak using HTTP POST
    try:
        response = requests.post(THINGSPEAK_URL, params=payload)
        if response.status_code == 200:
            print(f"Sent data: {distance} to ThingSpeak")
        else:
            print(f"Failed to send data: HTTP {response.status_code}")
    except Exception as e:
        print(f"Failed to send data: {e}")

try:
    while True:
        # Read the sensor
        distance = read_distance()
        print(f"IR Sensor Distance: {distance}")

        # Send data to ThingSpeak
        send_data_to_thingspeak(distance)

        # Wait 15 seconds between readings (to respect ThingSpeak rate limit)
        time.sleep(15)

except KeyboardInterrupt:
    print("Script interrupted by user.")

finally:
    # Clean up GPIO
    GPIO.cleanup()
