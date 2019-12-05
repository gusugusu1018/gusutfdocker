#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#include "mnist.h"

int main(int argc, const char* argv[])
{
	std::cout << "OpenCV :" << CV_VERSION << std::endl;

	std::cout << "init dataset..." << std::endl;
	std::vector<std::vector<float> > train_data;
	std::vector<float> label_data;
	Mnist mnist;
	train_data = mnist.readTrainingFile("../../data/train-images-idx3-ubyte");
	label_data = mnist.readLabelFile("../../data/train-labels-idx1-ubyte");
	cv::Mat image(28, 28, CV_8UC1);
	std::cout << "dims: " << image.dims \
		<< "\ndepth(byte/channel):" << image.elemSize1() \
		<< "\nchannels: " << image.channels() << std::endl;

	int k=0;
	std::cout << "target : " << k << std::endl;
	for (int j=0;j<28;j++) {
		for (int i=0;i<28;i++) {
			if (train_data[k][i+j*28]!=0) {
				std::cout <<" "<< train_data[k][i+j*28];
			}else {
				std::cout<<"  ";
			}
			image.at<unsigned char>(j,i) = train_data[k][i+j*28];
		}
		std::cout<<std::endl;
	}
	std::cout<<"label : "<<label_data[k]<<std::endl;
	cv::imwrite("test.png",image);
	return 0;
}
