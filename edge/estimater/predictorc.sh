#!/bin/bash
start_time=`date +%s%N`
./main.out ../models/tflitemodel_201912051415.tflite balt_test_raw.png 0.1
end_time=`date +%s%N`
run_time=`echo "scale=3; (${end_time} - ${start_time})/1000000000" | bc`
echo "${run_time} sec"
