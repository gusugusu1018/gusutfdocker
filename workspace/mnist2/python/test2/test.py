#!/usr/bin/env python3
# coding: utf-8
import numpy as np
import tensorflow as tf
import cv2

IMG_FILE = "test.png"
img = cv2.imread(IMG_FILE, cv2.IMREAD_GRAYSCALE)
data = np.asarray( img, dtype="int32" )
data = data / 255.0
input_data = np.expand_dims(data,0).astype(np.float32)

# Get interpreter from tflite model
interpreter = tf.lite.Interpreter(model_path="../../models/mnist_model.tflite")
interpreter.allocate_tensors()

# Set input data
input_details = interpreter.get_input_details()
interpreter.set_tensor(input_details[0]['index'], input_data)

# run estimater
interpreter.invoke()

# Get output data
output_details = interpreter.get_output_details()
output_data = interpreter.get_tensor(output_details[0]['index'])

print("== Input details ==")
print("name:", input_details[0]['name'])
print("shape:", input_details[0]['shape'])
print("type:", input_details[0]['dtype'])
print("\n== Output details ==")
print("name:", output_details[0]['name'])
print("shape:", output_details[0]['shape'])
print("type:", output_details[0]['dtype'])
print("\nDUMP INPUT")
print(interpreter.get_input_details()[0])
print("\nDUMP OUTPUT")
print(interpreter.get_output_details()[0])

print("\n== Result ==")
print("Prediction results:", output_data)
print("Predicted value:", np.argmax(output_data))
