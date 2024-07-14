import os
import time

import cv2
import numpy as np
import matplotlib.image as mpimg
import matplotlib.pyplot as plt
import tensorflow as tf

from vision import myUnet, predict_image

def has_sufficient_white_pixels(cell, threshold=1.6):
    """Check if the cell has at least the specified percentage of white pixels."""
    white_pixel_count = np.sum(np.all(cell == [255, 255, 255], axis=-1))
    total_pixels = cell.shape[0] * cell.shape[1]
    white_pixel_percentage = (white_pixel_count / total_pixels) * 100
    return white_pixel_percentage >= threshold

def grid_view(image, horizontal_cells, vertical_cells, threshold=1.6):
    """Draw a grid on the image and mark cells with sufficient white pixels."""
    cell_width = image.shape[1] // horizontal_cells
    cell_height = image.shape[0] // vertical_cells

    for i in range(horizontal_cells):
        for j in range(vertical_cells):
            start_x = i * cell_width
            start_y = j * cell_height
            end_x = start_x + cell_width
            end_y = start_y + cell_height

            cell = image[start_y:end_y, start_x:end_x]

            if has_sufficient_white_pixels(cell, threshold):
                cv2.rectangle(image, (start_x, start_y), (end_x, end_y), (0, 255, 0), 2)

    return image

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

def main():
    myunet = myUnet()
    model = myunet.get_unet()
    model.load_weights('unet.hdf5')

    image_path = '23.jpg'
    images = predict_image(model, image_path)

    camera_range = 500  # Example camera range in cm
    nozzle_activation = 50  # Example nozzle activation in cm
    vertical_cells = int(camera_range / nozzle_activation)
    nozzle_number = 4  # Assuming nozzles are equidistant

    signals = nozzle_control(images, vertical_cells)
    print("Signals:")
    print(signals[:5])

    plt.imshow(grid_view(images, nozzle_number, vertical_cells))
    plt.savefig("0out.jpg")

if __name__ == "__main__":
    main()
