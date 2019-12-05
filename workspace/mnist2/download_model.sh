#!/bin/bash
if [ ! -d models ];then
	mkdir models
fi
cd models
wget https://github.com/take-iwiw/CNN_NumberDetector/raw/master/05_TensorflowLite_CPP/resource/conv_mnist.tflite
wget https://github.com/frogermcs/MNIST-TFLite/raw/master/notebooks/mnist_model.tflite
