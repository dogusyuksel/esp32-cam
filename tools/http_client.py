import requests
import cv2
import numpy as np
from io import BytesIO
import time
import sys

# ESP32 IP address
param_1 = ""
try:
    param_1 = sys.argv[1]
except:
    param_1 = "172.20.10.14"
ESP32_IP = 'http://'+ param_1 +'/jpegstream'

def get_jpeg_stream():
    response = requests.get(ESP32_IP, stream=True)
    if response.status_code == 200:
        return response.iter_content(chunk_size=1024)
    else:
        print(f"Failed to connect to ESP32: {response.status_code}")
        return None

def process_stream(stream):
    jpeg_data = b""
    for chunk in stream:
        jpeg_data += chunk
        start = jpeg_data.find(b'\xff\xd8')
        end = jpeg_data.find(b'\xff\xd9')
        if start != -1 and end != -1:
            jpg = jpeg_data[start:end+2]
            jpeg_data = jpeg_data[end+2:]
            yield jpg

def save_and_show_images():
    stream = get_jpeg_stream()
    if stream is None:
        return

    for i, jpeg in enumerate(process_stream(stream)):
        # Save the image
        # with open(f'image_{i}.jpg', 'wb') as f:
        #     f.write(jpeg)

        # Display the image
        try:
            image = cv2.imdecode(np.frombuffer(jpeg, np.uint8), cv2.IMREAD_COLOR)
            if image is not None:
                cv2.imshow('ESP32 Camera', image)
                if cv2.waitKey(1) == 27:  # Press 'Esc' to exit
                    break
            else:
                print("Failed to decode image")
        except:
            print("we are too fast to get image, buffer is null")

        # Simulate processing delay
        time.sleep(0.1)

    cv2.destroyAllWindows()

save_and_show_images()