This is the files for the autonomous bird feeder that will do the following:

- Provide a classification results based on the  object detection with a confidence of greater than 60%.

Currently classification result is provided on an image stored on the pi labelled "Bird_1.PNG"

Classification of the image requires cmake to build an executable file and the process is the following:

1. Naviagate to the build folder
2. In the terminal type cmake .
3. In the terminal type make
4. In the terminal type ./SSD_Classifier

Step 4 will run the executable and the classifier results will be shown in the terminal.

The results from classification are output to terminal and the image with the object detected boxes drawn ontop is saved locally as "Class_output1.jpg"

The main code and tutorials for installations required were provided by Q-engineering.
Permission was obtained to utilised the code obtained from their repository.

Any website urls provided are tested working as of 09/03/2021

Q-engineering github: https://github.com/Qengineering
Q-engineering website: https://qengineering.eu

To be able to run classification a number of steps must be followed. 

First TensorFlow lite must be installed on the Raspberry Pi. This will also require c++ API libraries to be built.
In our case we are using a Raspberry Pi 4 with a 32 bit OS.

To install TensorFlow lite with c++ API libraries a tutorial by Q-engineering was used and is available online at the following link:
https://qengineering.eu/install-tensorflow-2-lite-on-raspberry-pi-4.html

Secondly OpenCV4 must also be installed. 
A tutorial on how to do this for a 32 bit OS is provided by Q-engineering and is available online at:
https://qengineering.eu/install-opencv-4.5-on-rapsberry-pi-4.html

Thirdly the following files are required:
CMakeLists.txt
TFlite_Classifier.cpp
Bird_1.PNG
COCO_labels.txt
detect.tflite

The original code provided in a Code::Blocks implementation is provided by Q-Engineering at:
https://www.github.com/Qengineering/TensorFlow_Lite_SSD_RPi_32-bits

The original code is not required to run the classification but serves as the original source for the TFlite_Classifier.cpp file.
From this repositroy a CMakeLists.txt file was created and the TFlite_Classifier.cpp was modified.

The bird image is a royalty-free image captured by a member of our team.
