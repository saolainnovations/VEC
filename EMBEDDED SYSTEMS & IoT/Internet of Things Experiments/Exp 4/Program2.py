import RPi.GPIO as GPIO
import time

# Set up the GPIO pin
GPIO.setmode(GPIO.BCM)
LED_PIN = 17
GPIO.setup(LED_PIN, GPIO.OUT)

try:
    while True:
        GPIO.output(LED_PIN, GPIO.HIGH)  # Turn on LED
        time.sleep(1)  # Wait for 1 second
        GPIO.output(LED_PIN, GPIO.LOW)   # Turn off LED
        time.sleep(1)  # Wait for 1 second
except KeyboardInterrupt:
    print("Blinking stopped by user")
    GPIO.cleanup()  # Reset GPIO settings
