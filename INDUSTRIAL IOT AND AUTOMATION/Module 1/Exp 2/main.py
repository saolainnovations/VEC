import RPi.GPIO as GPIO
import time

# Set up the GPIO mode
GPIO.setmode(GPIO.BCM)

# Define the GPIO pin connected to the IR sensor
IR_SENSOR_PIN = 17

# Set up the IR sensor pin as an input
GPIO.setup(IR_SENSOR_PIN, GPIO.IN)

try:
    while True:
        # Read the sensor value
        sensor_value = GPIO.input(IR_SENSOR_PIN)
        
        # Print the sensor value (0 or 1)
        if sensor_value == 0:
            print("Object Detected")
        else:
            print("No Object Detected")
        
        # Wait for 4 seconds
        time.sleep(4)

except KeyboardInterrupt:
    # Clean up GPIO on CTRL+C exit
    GPIO.cleanup()

except Exception as e:
    print(f"An error occurred: {e}")
    GPIO.cleanup()

finally:
    # Clean up GPIO on normal exit
    GPIO.cleanup()
