//test test
#include <filesystem>
#include <iostream>
#include <gtest/gtest.h>
#include "BirdCam.h"
#include "USsensor.h"

namespace fs = std::experimental::filesystem;
fs::path p = "../../Photos/testImage.ppm";
BirdCam Test1;

const int trig = 18;
const int echo = 24;
Ultrasonic *Test2 = new Ultrasonic(trig, echo);
Ultrasonic *Test3 = new Ultrasonic(trig, echo);

TEST(sensorTest, photoTakenTest)
{
    bool exists = fs::exists(p);
    EXPECT_FALSE(exists);
    
    Test1.setFilePath("../../Photos/testImage.ppm");
    Test1.takePhoto();
    exists = fs::exists(p);
    EXPECT_TRUE(exists);
    remove("../../Photos/testImage.ppm");
}

TEST(sensorTest, USPositiveDistanceTest)
{   
    EXPECT_TRUE(Test2->measureDistance() > 0);
    delete Test2;
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

