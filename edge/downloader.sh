#!/bin/bash
WORKSPACE=$PWD
MODELFILE="tflitemodel_201912041514.tflite"
if [ ! -d $WORKSPACE/models ];then
	mkdir $WORKSPACE/models
fi
if [ ! -d $WORKSPACE/dataset ];then
	wget "https://drive.google.com/uc?export=download&id=1r7x945ca4aKrMf39YvYMc9gk3voi1ASm" -O "$WORKSPACE/dataset.zip"
	unzip "$WORKSPACE/dataset.zip"
fi
if [ ! -f $WORKSPACE/models/$MODELFILE ];then
	wget "https://drive.google.com/uc?export=download&id=10FIKWZeDPprySlz6ihcj1jkwnqidIIhd" -O "$WORKSPACE/models/$MODELFILE"
fi
