//test test
#include <filesystem>
#include <iostream>
#include <gtest/gtest.h>
#include "BirdCam.h"

namespace fs = std::experimental::filesystem;
fs::path p = "../Photos/testImage.ppm";
BirdCam Test1;

TEST(sensorTest, photoTakenTest)
{
    bool exists = fs::exists(p);
    EXPECT_FALSE(exists);
    
    Test1.setFilePath("../Photos/testImage.ppm");
    Test1.takePhoto();
    exists = fs::exists(p);
    EXPECT_TRUE(exists);
    remove("../Photos/testImage.ppm");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

