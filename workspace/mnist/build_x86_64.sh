#!/bin/bash
if [ -f libtensorflow-lite.a ]; then
	rm libtensorflow-lite.a
fi
TFDIR=~/tensorflow
ln -sf $TFDIR/tensorflow/lite/tools/make/gen/linux_x86_64/lib/libtensorflow-lite.a .
g++ main.cpp -o main.out \
	-I$TFDIR  \
	-I$TFDIR/tensorflow \
	-I$TFDIR/tensorflow/lite/tools/make/downloads \
	-I$TFDIR/tensorflow/lite/tools/make/downloads/eigen \
	-I$TFDIR/tensorflow/lite/tools/make/downloads/absl \
	-I$TFDIR/tensorflow/lite/tools/make/downloads/gemmlowp \
	-I$TFDIR/tensorlow/lite/tools/make/downloads/neon_2_sse \
	-I$TFDIR/tensorflow/lite/tools/make/downloads/farmhash/src \
	-I$TFDIR/tensorflow/lite/tools/make/downloads/flatbuffers/include \
	-std=c++11 -lstdc++ -lm -lpthread -ltensorflow-lite -L.
