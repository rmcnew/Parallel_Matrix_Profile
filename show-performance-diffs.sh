#!/bin/sh
for j in ./test_data/performance/*.txt; do vimdiff $j ./actual_results/performance/`basename $j`; done

