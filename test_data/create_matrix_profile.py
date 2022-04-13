#!/bin/env python3

import argparse
import csv
import numpy
import stumpy

parser = argparse.ArgumentParser()
parser.add_argument("--input", dest='input_file', action="store", help="input_time_series CSV file")
parser.add_argument("--output", dest='output_file', action="store", help="output_time_series Matrix Profile CSV file")
args = parser.parse_args();

print(f"Reading input time series from {args.input_file} and writing Matrix Profile to {args.output_file}")

with open(args.input_file, 'r') as f:
    reader = csv.reader(f, delimiter=',')
    headers = next(reader)  # comment out if no header in input csv
    data = numpy.array(list(reader))

# get the data column
time_series = data[:,1].astype(float)

WINDOW_SIZE = 10

# calculate matrix profile
matrix_profile_set = stumpy.stump(time_series, WINDOW_SIZE)

# matrix profile set columns: 0 is matrix profile, 1, is matrix profile indices

matrix_profile = matrix_profile_set[:,0:2]

# write the matrix profile to output_file
numpy.savetxt(args.output_file, matrix_profile, fmt='%.18e, %d', delimiter=',')
	
