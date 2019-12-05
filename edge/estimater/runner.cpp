#include <cstdio>
#include <iostream>

#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/optional_debug_tools.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, const char* argv[])
{
	std::string imagefilename = argv[1];
	constexpr char modelfiles[64] = "../models/tflitemodel_201912051415.tflite";
	constexpr float resize_rate = 0.1;
	cv::Mat image = cv::imread(imagefilename.c_str(), cv::IMREAD_GRAYSCALE );
	cv::Mat intensityImage = image(cv::Rect(450,10,600,600));
	cv::Mat resizedImage, bitwisenotImage, inputImage;
	cv::resize(intensityImage, resizedImage, cv::Size(), resize_rate, resize_rate);
	cv::bitwise_not(resizedImage, bitwisenotImage);
	bitwisenotImage.convertTo(inputImage, CV_32FC1, 1.0 / 255);
	std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile(modelfiles);
	tflite::ops::builtin::BuiltinOpResolver resolver;
	tflite::InterpreterBuilder builder(*model, resolver);
	std::unique_ptr<tflite::Interpreter> interpreter;
	builder(&interpreter);
	interpreter->AllocateTensors();
	float* input = interpreter->typed_input_tensor<float>(0);
	memcpy(input, inputImage.reshape(0, 1).data, sizeof(float) * 1 * 60 * 60);
	interpreter->Invoke();
	float* probs = interpreter->typed_output_tensor<float>(0);
	float maxAcc = probs[0];
	int maxIdx = 0;
	for (int i = 1; i < 5; i++) {
		if (maxAcc < probs[i]) {
			maxAcc = probs[i];
			maxIdx = i;
		}
	}
	constexpr char labels[5][10] = {"baltan","metron","taiga","taro","ultraman"};
	std::cout << labels[maxIdx] << ","<< maxAcc*100 <<"%"<< std::endl;
	return 0;
}
