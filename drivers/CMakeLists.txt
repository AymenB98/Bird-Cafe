#####################################
cmake_minimum_required (VERSION 2.8) 
project (birdcafe_cam)
find_package(raspicam REQUIRED)
add_executable (birdcafe_raspicam run.cpp)  
target_link_libraries (birdcafe_raspicam ${raspicam_LIBS})
#####################################