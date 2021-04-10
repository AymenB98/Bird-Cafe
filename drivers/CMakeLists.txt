#####################################
cmake_minimum_required (VERSION 2.8) 
project (birdcafe_cam)

set(DRIVER_LIB
  BirdCam.cpp
  USsensor.cpp
  UDP.cpp
  )


find_package(raspicam REQUIRED)
find_package(OpenCV REQUIRED) 
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("/usr/local/include/opencv4")
#include_directories("../SSD_Classifier/")
find_package(Threads)


include_directories("/home/pi/tensorflow")
include_directories("/home/pi/tensorflow/tensorflow/lite/tools/make/downloads/flatbuffers/include")
include_directories("/home/pi/tensorflow/tensorflow/lite/tools/make/downloads/absl")


add_library(birdcafe_cam_static STATIC ${DRIVER_LIB})

add_executable (birdcafe_raspicam ${DRIVER_LIB} run.cpp) 

find_library(wiringPi_LIB wiringPi)

target_link_libraries (birdcafe_raspicam
	 ${raspicam_LIBS}
	 ${wiringPi_LIB}
	 "/home/pi/tensorflow/tensorflow/lite/tools/make/gen/rpi_armv7l/lib/libtensorflow-lite.a"
	 "/home/pi/tensorflow/tensorflow/lite/tools/make/downloads/flatbuffers/build/libflatbuffers.a"
	 "/lib/arm-linux-gnueabihf/libdl.so.2"	 
	 pthread
	 stdc++fs
	 ${OpenCV_Libs}
	 ${OpenCV_LIBS}
	 ${CMAKE_THREAD_LIBS_INIT}
)
#####################################