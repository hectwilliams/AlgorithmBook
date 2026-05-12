"""
    Quick review of logging and using parsing method in datetime, lots of assessments require time manipulation :)
"""
from  datetime import datetime
import csv 
import re

filename = "datetime.csv"

with open(filename, mode='r') as file:
    reader = csv.reader(file)

    prev = None 
    delta = None 
    bins = [0]
    for i, row in enumerate(reader):
        if i:
            time_24 = re.match(r"\d{4}\-\d{2}\-\d{2}\s(\d{2}\:\d{2}\:\d{2})", row[1]).group(1)
            parse_24_obj = datetime.strptime(time_24, "%H:%M:%S")
            parse_12_str = parse_24_obj.strftime("%I:%M:%S %p")

            # 12 hour string to  24 hour parse object 
            parse_24 = datetime.strptime(parse_12_str, "%I:%M:%S %p")

            if i == 1:
                # init prev lookback-1 object
                prev  = parse_24

            delta = parse_24 - prev 
            if delta.total_seconds() < 0:
                # day has passed, sycn clocks , init a bin
                prev = parse_24
                # start new bin 
                bins += [1]
            else:
                # add events to bin that occur on same day
                bins[-1] += 1 
            pre = parse_24
    
    print(bins)

