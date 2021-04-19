//test test
//#ifdef TESTING
#include <filesystem>
#include <iostream>
#include <gtest/gtest.h>
#include "BirdCam.h"
#include "USsensor.h"
#include "UDP.h"
#include "latencyTimers.h"


namespace fs = std::experimental::filesystem;
fs::path p = "../../Photos/testImage.png";

fs::path tp1 = "../COCO_labels.txt";
fs::path tp2 = "../detect.tflite";
fs::path tp3 = "Bird_1.PNG";

BirdCam Test1;

const int trig = 18;
const int echo = 24;
Ultrasonic *Test2 = new Ultrasonic(trig, echo);
Ultrasonic *Test3 = new Ultrasonic(trig, echo);

Ultrasonic *Test4 = new Ultrasonic(trig,echo);

//Tests below for drivers
//By Joe Costello 2254254C

TEST(sensorTest, photoTakenTest)
{
    bool exists = fs::exists(p);
    EXPECT_FALSE(exists);
    

    Test1.setFilePath("../../Photos/testImage.png");
    Test1.takePhoto();
    exists = fs::exists(p);
    EXPECT_TRUE(exists);
    remove("../../Photos/testImage.png");
}

TEST(sensorTest, USPositiveDistanceTest)
{   
    EXPECT_TRUE(Test2->measureDistance() > 0);
    delete Test2;
}


// Tests for Tensorflow to included below
// By Jonathan Roarty 2254735R

TEST(TFTest, TFLiteLabelsTest)
 {
    //Test that checks to ensure that the COCO_labels.txt file is present
    bool present = fs::exists(tp1);
    EXPECT_TRUE(present);
    
    
 }

TEST(TFTest, TFLitedetectfileTest)
 {
    //Test that checks the detect.tflite file is present
    bool present = fs::exists(tp2);
    EXPECT_TRUE(present);
 }

TEST(TFTest, TestImageCheck)
{
    //Test checks that the test bird image is present
    bool present = fs::exists(tp3);
    EXPECT_TRUE(present);

}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//#endif

