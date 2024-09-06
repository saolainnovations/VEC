import RPi.GPIO as GPIO
import time
import requests

# Setup GPIO mode
GPIO.setmode(GPIO.BCM)

# Relay and Buzzer Pins
RELAY_PIN = 18
BUZZER_PIN = 27

# Setup GPIO pins
GPIO.setup(RELAY_PIN, GPIO.OUT)
GPIO.setup(BUZZER_PIN, GPIO.OUT)

# ThingSpeak API details
THINGSPEAK_CHANNEL_ID = "Your_Channel_ID"
THINGSPEAK_API_KEY = "Your_Read_API_Key"
THINGSPEAK_READ_URL = f"https://api.thingspeak.com/channels/{THINGSPEAK_CHANNEL_ID}/fields/5.json?api_key={THINGSPEAK_API_KEY}&results=1"

# Function to fetch the latest value of the switch (field 5 and field 6) from ThingSpeak
def get_thingspeak_data():
    try:
        response = requests.get(THINGSPEAK_READ_URL)
        data = response.json()
        relay_value = int(data['feeds'][0]['field5'])  # Field 5 is for relay
        buzzer_value = int(data['feeds'][0]['field6'])  # Field 6 is for buzzer
        return relay_value, buzzer_value
    except Exception as e:
        print("Error fetching data from ThingSpeak:", e)
        return None, None

# Main loop
try:
    while True:
        # Get the values for relay and buzzer from ThingSpeak
        relay_value, buzzer_value = get_thingspeak_data()

        if relay_value is not None and buzzer_value is not None:
            print(f"Relay: {relay_value}, Buzzer: {buzzer_value}")

            # Control relay based on the value in Field 5
            if relay_value == 1:
                GPIO.output(RELAY_PIN, GPIO.HIGH)  # Turn on relay
            else:
                GPIO.output(RELAY_PIN, GPIO.LOW)  # Turn off relay

            # Control buzzer based on the value in Field 6
            if buzzer_value == 1:
                GPIO.output(BUZZER_PIN, GPIO.HIGH)  # Turn on buzzer
            else:
                GPIO.output(BUZZER_PIN, GPIO.LOW)  # Turn off buzzer

        # Wait for some time before checking again
        time.sleep(10)  # Fetch every 10 seconds

except KeyboardInterrupt:
    print("Process interrupted by user")
    GPIO.cleanup()
