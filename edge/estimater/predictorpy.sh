#!/bin/bash
start_time=`date +%s%N`
./intensity_cropper.out balt_test_raw.png 0.1
python3 main.py ../models/tflitemodel_201912051400.tflite temp.png
end_time=`date +%s%N`
run_time=`echo "scale=3; (${end_time} - ${start_time})/1000000000" | bc`
echo "${run_time} sec"
