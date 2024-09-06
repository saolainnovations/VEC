import time
import RPi.GPIO as GPIO
import Adafruit_DHT
import paho.mqtt.client as mqtt

# ThingSpeak details
THINGSPEAK_CHANNEL_ID = "Your_Channel_ID"
THINGSPEAK_API_KEY = "Your_API_Key"
THINGSPEAK_MQTT_HOST = "mqtt.thingspeak.com"
THINGSPEAK_PORT = 1883
THINGSPEAK_TOPIC = "channels/" + THINGSPEAK_CHANNEL_ID + "/publish/" + THINGSPEAK_API_KEY

# Setup GPIO mode
GPIO.setmode(GPIO.BCM)

# Ultrasonic sensor pins
TRIG = 23
ECHO = 24

# Soil moisture sensor pin
SOIL_MOISTURE_PIN = 17

# Set up GPIO pins
GPIO.setup(TRIG, GPIO.OUT)
GPIO.setup(ECHO, GPIO.IN)
GPIO.setup(SOIL_MOISTURE_PIN, GPIO.IN)

# Function to get distance from ultrasonic sensor
def get_distance():
    GPIO.output(TRIG, False)
    time.sleep(2)
    GPIO.output(TRIG, True)
    time.sleep(0.00001)
    GPIO.output(TRIG, False)

    while GPIO.input(ECHO) == 0:
        pulse_start = time.time()

    while GPIO.input(ECHO) == 1:
        pulse_end = time.time()

    pulse_duration = pulse_end - pulse_start
    distance = pulse_duration * 17150
    distance = round(distance, 2)

    return distance

# Function to get soil moisture data
def get_soil_moisture():
    if GPIO.input(SOIL_MOISTURE_PIN):
        return 1  # Dry
    else:
        return 0  # Wet

# MQTT publishing function
def publish_to_thingspeak(distance, soil_moisture):
    client = mqtt.Client()
    client.connect(THINGSPEAK_MQTT_HOST, THINGSPEAK_PORT, 60)
    payload = "field1=" + str(soil_moisture) + "&field2=" + str(distance)
    client.publish(THINGSPEAK_TOPIC, payload)
    client.disconnect()

# Main loop
try:
    while True:
        distance = get_distance()
        soil_moisture = get_soil_moisture()

        print(f"Distance: {distance} cm")
        print(f"Soil Moisture: {soil_moisture} (1 = Dry, 0 = Wet)")

        # Publish data to ThingSpeak
        publish_to_thingspeak(distance, soil_moisture)

        # Wait before next reading
        time.sleep(20)  # every 20 seconds

except KeyboardInterrupt:
    print("Measurement stopped by user")
    GPIO.cleanup()
