#!/bin/sh
for j in ./test_data/output_matrix_profiles/*.csv; do ./compute-percent-diff.py --expected $j --actual ./actual_results/`basename $j`; done
