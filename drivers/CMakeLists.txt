#####################################
cmake_minimum_required (VERSION 2.8) 
project (birdcafe_cam)

set(DRIVER_LIB
  BirdCam.cpp
  USsensor.cpp)


find_package(raspicam REQUIRED)

add_library(birdcafe_cam_static STATIC ${DRIVER_LIB})

add_executable (birdcafe_raspicam ${DRIVER_LIB} run.cpp) 

find_library(wiringPi_LIB wiringPi)

target_link_libraries (birdcafe_raspicam ${raspicam_LIBS} ${wiringPi_LIB} pthread stdc++fs)
#####################################