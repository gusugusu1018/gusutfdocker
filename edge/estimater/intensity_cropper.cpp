#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>

int main(int argc, const char* argv[])
{
	std::string filename;
	float resize_rate;
	int initialIdx;
	if (argc == 3) {
		filename = argv[1];
		resize_rate = std::atof(argv[2]);
	} else {
		std::cout << "Please add input, output directories to arguments" << std::endl;
		return 1;
	}
	auto image = cv::imread(filename.c_str(), cv::IMREAD_GRAYSCALE);
	if (image.empty()) {
		std::cout << "cannot open : " << filename << std::endl;
		return -1;
	}
	std::cout << "inpute file   : " << filename << std::endl;
	std::cout << "input size    : " << image.size << std::endl;
	std::cout << "resized image : " << resize_rate*600 <<"x"<<resize_rate*600 << std::endl;
	auto cropRange = cv::Rect(450,10,600,600);
	auto intensityImage = image(cropRange);
	cv::Mat resizedImage, bitwisenotImage;
	cv::resize(intensityImage, resizedImage, cv::Size(), resize_rate, resize_rate);
	cv::bitwise_not(resizedImage, bitwisenotImage);
	cv::imwrite("temp.png", bitwisenotImage);
	return 0;
}
