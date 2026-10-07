import csv
from pathlib import Path
from statistics import median
import matplotlib.pyplot as plt

# Each request contains: ID, timestamp, mode, address, size, PID.
directory = Path(__file__).resolve().parent
traces = {}
answer_rows = []
# Conclusions below refer to the supplied v2 files.

for trace_path in sorted(directory.glob('trace_*.csv')):
    requests = []
    with trace_path.open() as csv_file:
        reader = csv.reader(csv_file)
        next(reader)  # Skip the header.
        for row in reader:
            request_id = int(row[0])
            timestamp = int(row[1])
            mode = row[2]
            address = int(row[3])
            request_size = int(row[4])
            process_id = int(row[5])
            requests.append((request_id, timestamp, mode, address, request_size, process_id))
    traces[trace_path.name] = requests


# Q1: Count all records, including records with invalid field values.
request_counts = {}
for filename, requests in traces.items():
    request_counts[filename] = len(requests)
answer_rows.append(('Q1', ', '.join(traces), f"{request_counts['trace_0.csv']} requests"))

# Q2: Find the latest timestamp in each file.
latest_timestamps = {}
for filename, requests in traces.items():
    latest_timestamp = requests[0][1]
    for request in requests:
        timestamp = request[1]
        if timestamp > latest_timestamp:
            latest_timestamp = timestamp
    latest_timestamps[filename] = latest_timestamp
answer_rows.append(('Q2', 'trace_2.csv', f"{latest_timestamps['trace_2.csv']} s"))

# Q3: Count the requests whose mode is 'w'.
write_counts = {}
for filename, requests in traces.items():
    write_count = 0
    for request in requests:
        mode = request[2]
        if mode == 'w':
            write_count += 1
    write_counts[filename] = write_count
answer_rows.append(('Q3', 'trace_3.csv', f"{write_counts['trace_3.csv']} writes"))

# Q4: Add the sizes of all write requests.
written_bytes = {}
for filename, requests in traces.items():
    total_bytes = 0
    for request in requests:
        mode = request[2]
        request_size = request[4]
        if mode == 'w':
            total_bytes += request_size
    written_bytes[filename] = total_bytes
answer_rows.append(('Q4', 'trace_4.csv', f"{written_bytes['trace_4.csv']} bytes"))

# Q5: Collect read sizes before calculating the median.
median_read_sizes = {}
for filename, requests in traces.items():
    read_sizes = []
    for request in requests:
        if request[2] == 'r':
            read_sizes.append(request[4])
    if read_sizes:  # Files with no reads have no read-size median.
        median_read_sizes[filename] = median(read_sizes)
answer_rows.append(('Q5', 'trace_1.csv', f"{median_read_sizes['trace_1.csv']} bytes"))

# Q6: The largest address + size gives a lower bound on capacity.
capacity_bounds = {}
for filename, requests in traces.items():
    required_capacity = 0
    for request in requests:
        address = request[3]
        request_size = request[4]
        end_address = address + request_size
        if end_address > required_capacity:
            required_capacity = end_address
    capacity_bounds[filename] = required_capacity
answer_rows.append(('Q6', 'trace_4.csv', f"{capacity_bounds['trace_4.csv']} bytes (lower bound)"))

# Q7: A set keeps each process ID only once.
process_counts = {}
for filename, requests in traces.items():
    process_ids = set()
    for request in requests:
        process_ids.add(request[5])
    process_counts[filename] = len(process_ids)
answer_rows.append(('Q7', 'trace_3.csv', f"{process_counts['trace_3.csv']} processes"))

# Q8: Count each process separately within its own file.
process_request_counts = {}
for filename, requests in traces.items():
    process_counts_in_file = {}
    for request in requests:
        process_id = request[5]
        if process_id not in process_counts_in_file:
            process_counts_in_file[process_id] = 0
        process_counts_in_file[process_id] += 1
    for process_id, request_count in process_counts_in_file.items():
        process_name = f'{filename}, PID {process_id}'
        process_request_counts[process_name] = request_count
answer_rows.append(('Q8', 'trace_2.csv, PID 9999', f"{process_request_counts['trace_2.csv, PID 9999']} requests"))

# Q9: Look for equal timestamps. This does not prove execution overlap.
simultaneous_submissions = {}
for filename, requests in traces.items():
    seen_timestamps = set()
    simultaneous_submissions[filename] = False
    for request in requests:
        timestamp = request[1]
        if timestamp in seen_timestamps:
            simultaneous_submissions[filename] = True
            break
        seen_timestamps.add(timestamp)
answer_rows.append(('Q9', 'trace_1.csv', 'Same timestamp'))

# Q10: Compare every request size with the first one.
constant_sizes = {}
for filename, requests in traces.items():
    first_size = requests[0][4]
    constant_sizes[filename] = True
    for request in requests:
        if request[4] != first_size:
            constant_sizes[filename] = False
            break
answer_rows.append(('Q10', 'trace_0.csv, trace_3.csv', 'Constant size'))

# Q11: Plot the sizes and compare the shapes visually.
plt.figure(figsize=(12, 7))
plot_number = 1
for filename, requests in traces.items():
    request_sizes = []
    for request in requests:
        request_sizes.append(request[4] / 1024)  # Convert bytes to KiB.
    plt.subplot(2, 3, plot_number)
    if len(set(request_sizes)) == 1:
        plt.hist(request_sizes, bins=10, range=(0, request_sizes[0] * 2), edgecolor='white')
    else:
        plt.hist(request_sizes, bins=len(set(request_sizes)), edgecolor='white')
    plt.title(filename)
    plt.xlabel('Request size (KiB)')
    plt.ylabel('Number of requests')
    plot_number += 1
plt.tight_layout()
plt.savefig(directory / 'q11_size_distribution.png', dpi=150)
plt.close()
# Visual conclusion for the supplied v2 files, not an automatic test.
answer_rows.append(('Q11', 'trace_2.csv, trace_4.csv',
                    'Approximately normal by visual inspection; see q11_size_distribution.png'))

# Q12: Count consecutive reads in file order, across all processes.
longest_read_streams = {}
for filename, requests in traces.items():
    current_length = 0
    longest_length = 0
    for request in requests:
        if request[2] == 'r':
            current_length += 1
        else:
            current_length = 0
        if current_length > longest_length:
            longest_length = current_length
    longest_read_streams[filename] = longest_length
answer_rows.append(('Q12', 'trace_2.csv', f"{longest_read_streams['trace_2.csv']} reads (all processes)"))

# Q13: Compare both with and without the request ID.
duplicate_requests = {}
repeated_operations = {}
duplicate_counts = {}
operation_repeat_counts = {}
for filename, requests in traces.items():
    seen_requests = set()
    seen_operations = set()
    duplicate_requests[filename] = False
    repeated_operations[filename] = False
    duplicate_counts[filename] = 0
    operation_repeat_counts[filename] = 0
    for request in requests:
        request_id, timestamp, mode, address, request_size, process_id = request
        operation = (mode, address, request_size, process_id)
        request_without_time = (request_id, mode, address, request_size, process_id)
        if request_without_time in seen_requests:
            duplicate_requests[filename] = True
            duplicate_counts[filename] += 1
        if operation in seen_operations:
            repeated_operations[filename] = True
            operation_repeat_counts[filename] += 1
        seen_requests.add(request_without_time)
        seen_operations.add(operation)
# Counts are extra occurrences after the first matching operation.
answer_rows.append(('Q13', 'trace_1.csv, trace_3.csv',
                    f"IDs ignored: {operation_repeat_counts['trace_1.csv']}, "
                    f"{operation_repeat_counts['trace_3.csv']} extra occurrences; "
                    f"IDs included: {sum(duplicate_counts.values())}"))

# Q14: Report exact field problems. A negative ID is suspicious under
# the observed non-negative indexing pattern, not a CSV syntax error.
invalid_fields = {}
for filename, requests in traces.items():
    invalid_records = []
    for line_number, request in enumerate(requests, 2):
        request_id, timestamp, mode, address, request_size, process_id = request
        reasons = []
        if request_id < 0:
            reasons.append(f'suspicious ID {request_id}')
        if mode not in ('r', 'w'):
            reasons.append(f"invalid mode '{mode}'")
        if timestamp < 0 or address < 0 or process_id < 0:
            reasons.append('negative timestamp, address or PID')
        if request_size <= 0:
            reasons.append('non-positive size')
        if reasons:
            invalid_records.append((line_number, request))
    invalid_fields[filename] = invalid_records
# Line numbers include the header as line 1.
negative_id_line, negative_id_request = invalid_fields['trace_0.csv'][0]
invalid_mode_line, invalid_mode_request = invalid_fields['trace_1.csv'][0]
answer_rows.append(('Q14', 'trace_0.csv, trace_1.csv',
                    f'trace_0.csv L{negative_id_line}: suspicious ID {negative_id_request[0]}; '
                    f"trace_1.csv L{invalid_mode_line}: invalid mode '{invalid_mode_request[2]}'"))

# Q15: Measure the first-to-last submission span, not completion time.
submission_durations = {}
for filename, requests in traces.items():
    timestamps = []
    for request in requests:
        timestamps.append(request[1])
    first_timestamp = min(timestamps)
    last_timestamp = max(timestamps)
    submission_durations[filename] = last_timestamp - first_timestamp
answer_rows.append(('Q15', 'trace_2.csv', f"{submission_durations['trace_2.csv']} s (last - first submission)"))

# Align the three columns after all 15 answers have been collected.
header = ('Question', 'File / process', 'Result')
column_widths = [len(header[0]), len(header[1]), len(header[2])]
for row in answer_rows:
    for column in range(3):
        column_widths[column] = max(column_widths[column], len(row[column]))
answer_lines = []
for row in [header] + answer_rows:
    cells = []
    for column in range(3):
        cells.append(row[column].ljust(column_widths[column]))
    answer_lines.append('| ' + ' | '.join(cells) + ' |')
separator = '|'
for width in column_widths:
    separator += '-' * (width + 2) + '|'
answer_lines.insert(1, separator)
answer_text = '\n'.join(answer_lines) + '\n'
(directory / 'answers.txt').write_text(answer_text, encoding='utf-8')
print(answer_text, end='')
