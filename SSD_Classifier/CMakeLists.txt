cmake_minimum_required(VERSION "3.13.4") 

project("SSD_Classifier")


find_package(OpenCV REQUIRED) 
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("/usr/local/include/opencv4")

find_package(Threads)


include_directories("/home/pi/tensorflow")
include_directories("/home/pi/tensorflow/tensorflow/lite/tools/make/downloads/flatbuffers/include")
include_directories("/home/pi/tensorflow/tensorflow/lite/tools/make/downloads/absl")


add_executable("${PROJECT_NAME}" "TFlite_Classifier.cpp")
target_link_libraries( "${PROJECT_NAME}" ${OpenCV_Libs})
target_link_libraries( "${PROJECT_NAME}" "/home/pi/tensorflow/tensorflow/lite/tools/make/gen/rpi_armv7l/lib/libtensorflow-lite.a")
target_link_libraries( "${PROJECT_NAME}" "/home/pi/tensorflow/tensorflow/lite/tools/make/downloads/flatbuffers/build/libflatbuffers.a")
target_link_libraries( "${PROJECT_NAME}" "/lib/arm-linux-gnueabihf/libdl.so.2")
target_link_libraries( "${PROJECT_NAME}" ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries( "${PROJECT_NAME}" ${OpenCV_LIBS})






