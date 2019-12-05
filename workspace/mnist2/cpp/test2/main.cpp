#include <stdio.h>
#include <iostream>

#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/optional_debug_tools.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#define MODEL_FILENAME "../../models/mnist_model.tflite"

#define TFLITE_MINIMAL_CHECK(x)                              \
	if (!(x)) {                                                \
		fprintf(stderr, "Error at %s:%d\n", __FILE__, __LINE__); \
		exit(1);                                                 \
	}


int main()
{
	std::cout << "OpenCV :" << CV_VERSION << std::endl;
	cv::Mat image = cv::imread("test.png", cv::IMREAD_GRAYSCALE );
	if (image.empty()) {
		std::cerr <<  "Could not open or find the image" << std::endl ;
		return -1;
	}
	image.convertTo(image, CV_32FC1, 1.0 / 255);
	std::cout << "size : " << image.size << std::endl;

	/* tflite */
	std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile(MODEL_FILENAME);
	TFLITE_MINIMAL_CHECK(model != nullptr);

	// Build the interpreter
	tflite::ops::builtin::BuiltinOpResolver resolver;
	tflite::InterpreterBuilder builder(*model, resolver);
	std::unique_ptr<tflite::Interpreter> interpreter;
	builder(&interpreter);
	TFLITE_MINIMAL_CHECK(interpreter != nullptr);

	// Allocate tensor buffers.
	TFLITE_MINIMAL_CHECK(interpreter->AllocateTensors() == kTfLiteOk);
	//printf("=== Pre-invoke Interpreter State ===\n");
	//tflite::PrintInterpreterState(interpreter.get());

	// Set data to input tensor
	float* input = interpreter->typed_input_tensor<float>(0);
	memcpy(input, image.reshape(0, 1).data, sizeof(float) * 1 * 28 * 28);
	//memset(input, 0, sizeof(float) * 1 * 28 * 28);
	// Run inference
	TFLITE_MINIMAL_CHECK(interpreter->Invoke() == kTfLiteOk);
	//printf("\n\n=== Post-invoke Interpreter State ===\n");
	//tflite::PrintInterpreterState(interpreter.get());
	// Get data from output tensor
	float* probs = interpreter->typed_output_tensor<float>(0);
	for (int i = 0; i < 10; i++) {
		printf("prob of %d: %.3f\n", i, probs[i]);
	}
	return 0;
}
