cmake_minimum_required(VERSION 2.8)
project(DriverTests)

include_directories(${GTEST_INCLUDE_DIRS} "${TEST_SOURCE_DIR}..")

set(DRIVER_LIB
  ../BirdCam.cpp
  ../USsensor.cpp
  ../UDP.cpp
  )

find_package(GTest REQUIRED)
find_package(raspicam REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("/usr/local/include/opencv4")
find_package(Threads)

include_directories("/home/pi/tensorflow")
include_directories("/home/pi/tensorflow/tensorflow/lite/tools/make/downloads/flatbuffers/include")
include_directories("/home/pi/tensorflow/tensorflow/lite/tools/make/downloads/absl")

add_library(birdcafe_cam_test STATIC ${DRIVER_LIB})

add_executable(runTests DriverTests.cpp
			"${TEST_SOURCE_DIR}../BirdCam.cpp"
			"${TEST_SOURCE_DIR}../BirdCam.h"
			"${TEST_SOURCE_DIR}../USsensor.h"
			"${TEST_SOURCE_DIR}../USsensor.cpp"
			"${TEST_SOURCE_DIR}../TFlite_Classifier.h"
			${DRIVER_LIB})

find_library(wiringPi_LIB wiringPi)

target_link_libraries(runTests 
		${GTEST_LIBRARIES} 
		${raspicam_LIBS} 
		pthread stdc++fs 
		${wiringPi_LIB}
 		"/home/pi/tensorflow/tensorflow/lite/tools/make/gen/rpi_armv7l/lib/libtensorflow-lite.a"
	 	"/home/pi/tensorflow/tensorflow/lite/tools/make/downloads/flatbuffers/build/libflatbuffers.a"
	 	"/lib/arm-linux-gnueabihf/libdl.so.2"	
		${OpenCV_Libs}
	 	${OpenCV_LIBS}
	 	${CMAKE_THREAD_LIBS_INIT}
)




