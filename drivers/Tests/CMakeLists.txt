cmake_minimum_required(VERSION 2.8)
project(DriverTests)

include_directories(${GTEST_INCLUDE_DIRS} "${TEST_SOURCE_DIR}..")


find_package(GTest REQUIRED)
find_package(raspicam REQUIRED)

add_executable(runTests DriverTests.cpp
			"${TEST_SOURCE_DIR}../BirdCam.cpp"
			"${TEST_SOURCE_DIR}../BirdCam.h")

target_link_libraries(runTests ${GTEST_LIBRARIES} ${raspicam_LIBS} pthread stdc++fs)




