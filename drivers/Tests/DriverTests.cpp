//test test
#include <filesystem>
#include <iostream>
#include <gtest/gtest.h>
#include "BirdCam.h"
#include "USsensor.h"


namespace fs = std::experimental::filesystem;
fs::path p = "../../Photos/testImage.ppm";

fs::path tp1 = "../COCO_labels.txt";
fs::path tp2 = "../detect.tflite";
fs::path tp3 = "Bird_1.PNG";

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
//TEST(TFTest, TFLiteAboveThresholdTest)
//{
   //Test image of a bird loaded in
   //Mat frame = imread("Bird_1.PNG");
   //string name = "bird";
   //OutClass used to store string of highest classification label
   //std::string OutClass;
   //OutConfidence used to store float of highest classification value
   //std::float OutConfidence;
  
   //Test4->detect_from_picture(frame, std::string* OutClass, std::float* OutConfidence);

   //Test pass if confidence of classification is above 40%
   //EXPECT_TRUE(OutConfidence >= 0.4); 
   //In function
   //*OutClass = top_label  << will need to make a top label in detect_from_picture which is det_index[1]
   //*OutConfidence =top_conf ^^^^^
   //Test pass if correctly determines picture contains a bird
   //EXPECT_EQUAL(OutClass, name);
   //delete Test4;
//}

//TEST(sensorTest, TFLiteLatancyTest)
//{
    //Clock initialised
    //chrono::steady_clock::time_point TF_Test_Start, TF_Test_End;

    //Clock starts here
    //TF_Test_Start = chrono::steady_clock::now();

    //Test image of a bird loaded in
    //Mat frame = imread("Bird_1.PNG");
   
   //OutClass used to store string of highest classification label
   //std::string OutClass;
   //OutConfidence used to store float of highest classification value
   //std::float OutConfidence;
  
   //Test5->detect_from_picture(frame, std::string* OutClass, std::float* OutConfidence);

    //Clock ends here
    //TF_Test_End = chrono::steady_clock::now();
    //Total time for classification of test image calculated
    //float TF_Test_Duration =chrono::duration_cast <chrono::milliseconds> (TF_Test_Start - TF_Test_End).count();

    //Test passes if test takes less than 500ms
    //EXPECT_TRUE(TF_Test_Duration <= 500)
   //delete Test5;
// }

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

