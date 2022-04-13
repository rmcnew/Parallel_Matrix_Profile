#!/bin/sh
for j in ./test_data/output_matrix_profiles/*.csv; do vimdiff $j ./actual_results/`basename $j`; done
