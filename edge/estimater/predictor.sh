#!/bin/bash
IMAGE=$1
start_time=`date +%s%N`
OUTPUT=`./runner.out ${IMAGE}`
end_time=`date +%s%N`
run_time=`echo "scale=3; (${end_time} - ${start_time})/1000000000" | bc`
echo "${OUTPUT},${run_time}sec"
