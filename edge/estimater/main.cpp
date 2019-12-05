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
	std::string modelfile, imagefilename;
	float resize_rate;
	if (argc == 4) {
		modelfile = argv[1];
		imagefilename = argv[2];
		resize_rate = std::atof(argv[3]);
	} else {
		std::cout << "Please add model,test files to arguments" << std::endl;
		return 1;
	}

	cv::Mat image = cv::imread(imagefilename.c_str(), cv::IMREAD_GRAYSCALE );
	if (image.empty()) {
		std::cerr <<  "Could not open or find the image" << std::endl ;
		return -1;
	}
	std::cout << "OpenCV        : " << CV_VERSION << std::endl;
	std::cout << "model file    : " << modelfile << std::endl;
	std::cout << "image file    : " << imagefilename << std::endl;
	std::cout << "input size    : " << image.size << std::endl;
	std::cout << "resized image : " << resize_rate*600 <<"x"<<resize_rate*600 << std::endl;

	auto cropRange = cv::Rect(450,10,600,600);
	auto intensityImage = image(cropRange);
	cv::Mat resizedImage, bitwisenotImage, inputImage;
	cv::resize(intensityImage, resizedImage, cv::Size(), resize_rate, resize_rate);
	cv::bitwise_not(resizedImage, bitwisenotImage);
	bitwisenotImage.convertTo(inputImage, CV_32FC1, 1.0 / 255);

	std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile(modelfile.c_str());
	if (model == nullptr)
		std::cerr << "model not found" << std::endl;
	tflite::ops::builtin::BuiltinOpResolver resolver;
	tflite::InterpreterBuilder builder(*model, resolver);
	std::unique_ptr<tflite::Interpreter> interpreter;
	builder(&interpreter);
	if (interpreter == nullptr)
		std::cerr << "interpreter cannot build" << std::endl;
	if (interpreter->AllocateTensors() != kTfLiteOk)
		std::cerr << "cannot allocate tensors" << std::endl;
	float* input = interpreter->typed_input_tensor<float>(0);
	memcpy(input, inputImage.reshape(0, 1).data, sizeof(float) * 1 * 60 * 60);
	if (interpreter->Invoke() != kTfLiteOk)
		std::cerr << "cannot invoke()"<< std::endl;
	float* probs = interpreter->typed_output_tensor<float>(0);
	for (int i = 0; i < 5; i++) {
		printf("prob of %d: %.3f\n", i, probs[i]);
	}
	return 0;
}
