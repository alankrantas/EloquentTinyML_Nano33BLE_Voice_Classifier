# EloquentTinyML Voice Classifier on Arduino Nano 33 BLE Sense

This is the code I've used in my [Hackster.io project](https://www.hackster.io/alankrantas/eloquenttinyml-easier-voice-classifier-on-nano-33-ble-sense-ebb81e):

* Use the same mic on Nano 33 BLE Sense for voice data collection/classfication
* Use standard Python and scikit-learn/Tensorflow 2 for neural network model training
* Very easy Tensorflow model deployment with one script and one model file

![image](https://raw.githubusercontent.com/alankrantas/EloquentTinyML_Nano33BLE_Voice_Classifier/main/Figure_1.png)

This is based on Simone Salerno's [blog article](https://eloquentarduino.github.io/2020/08/better-word-classification-with-arduino-33-ble-sense-and-machine-learning/) as well as his EloquentTinyML library.

Requirements:

* Python 3 64-bit with Tensorflow 2, NumPy, matplotlib, scikit-learn and [tinymlgen](https://github.com/eloquentarduino/tinymlgen)
* Install [Arduino nRF528x Boards](https://www.arduino.cc/en/Guide/NANO33BLESense) support and [EloquentTinyML](https://github.com/eloquentarduino/EloquentTinyML) library in Arduino IDE
