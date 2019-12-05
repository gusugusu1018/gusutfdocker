#!/usr/bin/env python3
# coding: utf-8
import sys
import numpy as np
import tensorflow as tf
from tensorflow.keras.preprocessing.image import img_to_array, load_img

if len(sys.argv) !=3:
    print("set argument")
    sys.exit()
MODELFILE = sys.argv[1]
IMAGEFILE = sys.argv[2]
print("model file    : ",MODELFILE)
print("image file    : ",IMAGEFILE)
interpreter = tf.lite.Interpreter(model_path=MODELFILE)
interpreter.allocate_tensors()
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()
print("input shape   : ",input_details[0]['shape'])
img = load_img(IMAGEFILE, color_mode='grayscale', target_size=(input_details[0]['shape'][1],input_details[0]['shape'][2]))
input_img = np.expand_dims(img_to_array(img)/255,0).astype(np.float32)
interpreter.set_tensor(input_details[0]['index'], input_img)
interpreter.invoke()
probs = interpreter.get_tensor(output_details[0]['index'])
result = np.argmax(probs[0])
score = probs[0][result]
class_li = ['balt', 'metr', 'taig', 'taro', 'ultr']
print("result        : ",class_li[result],"class   -  accuracy " ,score)
sys.exit()
