FROM tensorflow/tensorflow:nightly-jupyter
LABEL maintainer="gusugusu1018 <gusugusu1018@gmail.com>"
WORKDIR /root
RUN apt-get update && apt-get upgrade -y && apt-get install -y \
	build-essential \
	crossbuild-essential-arm64 \
	crossbuild-essential-armhf \
	git unzip wget zlib1g-dev
RUN git clone https://github.com/tensorflow/tensorflow.git \
	&& cd tensorflow \
	&& ./tensorflow/lite/tools/make/download_dependencies.sh \
	&& ./tensorflow/lite/tools/make/build_aarch64_lib.sh \
	&& ./tensorflow/lite/tools/make/build_rpi_lib.sh \
	&& ./tensorflow/lite/tools/make/build_lib.sh
