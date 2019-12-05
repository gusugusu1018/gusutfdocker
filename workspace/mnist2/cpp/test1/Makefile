all:
	g++ main.cpp -o main.out \
		-I/opt/tensorflow  \
		-I/opt/tensorflow/tensorflow \
		-I/opt/tensorflow/tensorflow/lite/tools/make/downloads \
		-I/opt/tensorflow/tensorflow/lite/tools/make/downloads/eigen \
		-I/opt/tensorflow/tensorflow/lite/tools/make/downloads/absl \
		-I/opt/tensorflow/tensorflow/lite/tools/make/downloads/gemmlowp \
		-I/opt/tensorflow/tensorlow/lite/tools/make/downloads/neon_2_sse \
		-I/opt/tensorflow/tensorflow/lite/tools/make/downloads/farmhash/src \
		-I/opt/tensorflow/tensorflow/lite/tools/make/downloads/flatbuffers/include \
		-std=c++11 -lstdc++ -lm -lpthread -ltensorflow-lite
clean:
	rm main.out
