import csv
import random
from pathlib import Path

random.seed(0)
timestamp = 0
start_address = 0
with Path(__file__).with_name('generated.csv').open('w', newline='') as csv_file:
    csv_writer = csv.writer(csv_file)
    csv_writer.writerow(['index', 'timestamp', 'mode', 'address', 'size'])
    for request_id in range(100):
        timestamp += random.randint(1, 5)
        if request_id % 5 < 3:
            mode = 'r'
        else:
            mode = 'w'
        request_size = 0
        while request_size <= 0:
            request_size = round(random.gauss(4096, 1024))
        csv_writer.writerow([request_id, timestamp, mode, start_address, request_size])
        start_address += request_size
