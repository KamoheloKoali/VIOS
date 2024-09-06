import cv2
import numpy as np
from ultralytics import YOLO
import json
from datetime import datetime
import os

# Load the pre-trained YOLOv8 model
model = YOLO("yolov8s.pt")

def get_details(results):
    """
    Extracts the names, confidence, and bounding boxes for detected objects.
    """
    if not results or len(results) == 0:
        return

    class_names = results[0].names  # Names are stored in results[0].names

    for result in results:
        detection_count = len(result.boxes)  # Access detection count properly

        for i in range(detection_count):
            # Extract class ID, confidence, and bounding box
            cl = int(result.boxes.cls[i].item())
            name = class_names[cl]  # Get the class name
            confidence = float(result.boxes.conf[i].item())
            bounding_box = result.boxes.xyxy[i].cpu().numpy()

            x = int(bounding_box[0])
            y = int(bounding_box[1])
            width = int(bounding_box[2] - x)
            height = int(bounding_box[3] - y)

            # Return the detected object details
            yield name, {
                'box': [x, y, width, height],
                'confidence': confidence
            }

def detect_objects_yolov8(image):
    # Ensure the image is a NumPy array and in RGB format
    if not isinstance(image, np.ndarray):
        image = np.array(image)

    if image.shape[2] != 3:
        raise ValueError("The image must be in RGB format.")

    # Perform inference on the image
    results = model(image)

    # Prepare detection data for JSON output
    detection_data = {'objects': []}

    # Use the get_names function to extract detection information
    for name, info in get_details(results):
        detection_data['objects'].append({
            'name': name,
            'box': info['box'],
            'confidence': info['confidence'],
            'percentage_confidence': info['confidence'] * 100
        })

    # File to store detection results
    json_file = "results_from_detection_model.json"

    # Check if the file exists, create it if not
    if os.path.exists(json_file):
        with open(json_file, "r") as file:
            file_data = json.load(file)
    else:
        file_data = {}

    # Add new detection data with current timestamp
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    file_data[timestamp] = detection_data

    # Save updated results to the JSON file
    with open(json_file, "w") as file:
        json.dump(file_data, file, indent=4)

    # Optionally return the results
    return detection_data
