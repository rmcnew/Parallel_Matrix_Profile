#!/bin/env python3

import argparse
import csv
import math

parser = argparse.ArgumentParser()
parser.add_argument("--expected", dest='expected_file', action="store", help="expected CSV file")
parser.add_argument("--actual", dest='actual_file', action="store", help="actual CSV file")
args = parser.parse_args();

average_mp_percent_difference = 0.0 

expected_data = []
actual_data = []

try:
    with open(args.expected_file, 'r') as expected_f:
        expected_reader = csv.reader(expected_f, delimiter=',')
        expected_data = list(expected_reader)
except FileNotFoundError:
    print(f"Could not find {args.expected_file}") 

try:
    with open(args.actual_file, 'r') as actual_f:
        actual_reader = csv.reader(actual_f, delimiter=',')
        actual_data = list(actual_reader)
except FileNotFoundError:
    print(f"Could not find {args.actual_file}")
        
if (len(expected_data) > 0 and len(actual_data) > 0):
    for i in range(len(expected_data)):
        #print(f"{i}:  expected_data: {expected_data[i]}, actual_data: {actual_data[i]}")
        expected_mp = float(expected_data[i][0])
        actual_mp = float(actual_data[i][0])
        mp_percent_difference = (math.fabs(expected_mp - actual_mp) / expected_mp) * 100.0
        average_mp_percent_difference += mp_percent_difference

    average_mp_percent_difference = average_mp_percent_difference / float(len(expected_data))

    print(f"{args.actual_file} average matrix profile percent difference: {average_mp_percent_difference:.9f}")
