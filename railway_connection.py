import time
import requests
import os

# Path to file written by LabVIEW
FILE_PATH = "C:/SensorData/latest_data.csv"
RAILWAY_API = ""

last_sent = ""

while True:
    try:
        if not os.path.exists(FILE_PATH):
            print("Waiting for LabVIEW to write the file...")
            time.sleep(2)
            continue

        with open(FILE_PATH, 'r') as file:
            line = file.readline().strip()

        # Only send if the content changed (new data)
        if line and line != last_sent:
            parts = line.split(',')
            if len(parts) == 9:
                payload = {
                    "mq2": float(parts[0]),
                    "mq2_alert": bool(int(parts[1])),
                    "mq9": float(parts[2]),
                    "mq9_alert": bool(int(parts[3])),
                    "mq135": float(parts[4]),
                    "mq135_alert": bool(int(parts[5])),
                    "temp": float(parts[6]),
                    "humidity": float(parts[7]),
                    "heat_index": float(parts[8])
                }

                response = requests.post(RAILWAY_API, json=payload)
                print("Data sent:", payload)
                print("Response:", response.status_code)

                last_sent = line
            else:
                print("Invalid format:", line)
    except Exception as e:
        print("Error:", e)

    time.sleep(2)
