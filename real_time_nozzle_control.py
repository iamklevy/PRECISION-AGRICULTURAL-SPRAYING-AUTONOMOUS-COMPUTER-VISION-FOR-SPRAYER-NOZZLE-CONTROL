import tensorflow as tf
import cv2
import numpy as np
import time
import RPi.GPIO as GPIO
from vision import myUnet, predict_image

def has_sufficient_white_pixels(cell, threshold=1.6):
    """Check if the cell has at least the specified percentage of white pixels."""
    white_pixel_count = np.sum(np.all(cell == [255, 255, 255], axis=-1))
    total_pixels = cell.shape[0] * cell.shape[1]
    white_pixel_percentage = (white_pixel_count / total_pixels) * 100
    return white_pixel_percentage >= threshold

def nozzle_control(image, vertical_cells, horizontal_cells=4, threshold=1.6):
    """Calculate the signal values for each cell based on white pixel percentage."""
    cell_width = image.shape[1] // horizontal_cells
    cell_height = image.shape[0] // vertical_cells

    signals = np.zeros((vertical_cells, horizontal_cells), dtype=int)

    for j in reversed(range(vertical_cells)):
        for i in range(horizontal_cells):
            start_x = i * cell_width
            start_y = j * cell_height
            end_x = start_x + cell_width
            end_y = start_y + cell_height

            cell = image[start_y:end_y, start_x:end_x]

            signal = 1 if has_sufficient_white_pixels(cell, threshold) else 0

            signals[vertical_cells - j - 1, i] = signal

    return signals

def output_data(subarray):
    """Output data to GPIO pins."""
    for i in range(4):
        GPIO.output(data_pins[i], subarray[i])
    GPIO.output(trigger_pin, GPIO.HIGH)
    time.sleep(0.01)  # Small pulse duration
    GPIO.output(trigger_pin, GPIO.LOW)

# Initialize U-Net model
myunet = myUnet()
model = myunet.get_unet()
model.load_weights('unet.hdf5')

# Setup GPIO mode
GPIO.setmode(GPIO.BCM)

# Define the GPIO pins
data_pins = [17, 18, 27, 22]  # Replace with your GPIO pins
trigger_pin = 23  # Replace with your GPIO pin for the trigger

# Setup the GPIO pins
for pin in data_pins:
    GPIO.setup(pin, GPIO.OUT)
GPIO.setup(trigger_pin, GPIO.OUT)

# Camera and processing settings
camera_range = 500  # Example camera range in cm
nozzle_activation = 50  # Example nozzle activation in cm
vertical_cells = int(camera_range / nozzle_activation)
nozzle_number = 4  # Assuming nozzles are equidistant

# Initialize camera
cap = cv2.VideoCapture(0)  # Open the default camera

if not cap.isOpened():
    print("Error: Could not open camera.")
    exit()

try:
    while True:
        ret, frame = cap.read()
        if not ret:
            print("Failed to capture image")
            break

        # Preprocess frame for prediction
        processed_frame = predict_image(model, frame)
        processed_frame = cv2.merge([processed_frame, processed_frame, processed_frame])

        # Get signals
        signals = nozzle_control(processed_frame, vertical_cells)[:5]

        # Output signals to GPIO
        for subarray in signals:
            output_data(subarray)
            time.sleep(0.1)  # Adjust delay as needed

except KeyboardInterrupt:
    print("Exiting...")

finally:
    # Cleanup GPIO and release camera
    GPIO.cleanup()
    cap.release()
    cv2.destroyAllWindows()
