#ifndef TFLITE_CLASSIFIER_H
#define TFLITE_CLASSIFIER_H

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>
#include <iostream>
#include <opencv2/core/ocl.hpp>
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/string_util.h"
#include "tensorflow/lite/examples/label_image/get_top_n.h"
#include "tensorflow/lite/model.h"
#include <cmath>
#include <cstdlib>
#include "/home/pi/projects/BirdCafe/Bird-Cafe/udp/UdpTx/udp_tx.h"

//Jonathan Roarty GUID: 2254735
//Header file for TFlite_Classifier.cpp
using namespace cv;
using namespace std;

const size_t width = 300;
const size_t height = 300;

//Mat image;
//Mat frame;

static bool getFileContent(std::string fileName);

void detect_from_picture(Mat &src, std::unique_ptr<tflite::FlatBufferModel> model);

#endif
