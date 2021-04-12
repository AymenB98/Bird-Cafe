//!**************************************************************
//! Joe Costello 02/04/2021
//! \file
//! \brief Header file for Ultrasonic class
//!**************************************************************

#ifndef _BCULTRASOUND_H
#define _BCULTRASOUND_H


#include <wiringPi.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <ostream>
#include "BirdCam.h"
//Jona header files
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
// UDP header
#include "../udp/UdpTx/udp_tx.h"


using namespace cv;
using namespace std;

const size_t width = 300;
const size_t height = 300;



//! Class used for interfacing ultrasonic sensor
class Ultrasonic : public BirdCam
{
    private:
    //initialisation
    const int speed_of_sound = 343;
    int trig;
    int echo;
    int running = 0; 
    
    std::thread* USThread = NULL;
    std::vector<std::string> Labels;
    
    float distanceCalcUS(float pulseTime);
    
    bool getFileContent(std::string fileName);
    void detect_from_picture(Mat &src);

    public:

    //! \brief Constructor for Ultrasonic class. Ultrasnoic(int TriggerPin, int EchoPin)
    Ultrasonic(int Trig, int Echo);
    
    //setters
    //! \brief Used to set trigger pin.
    void setTrigger(int Trig);

    //! \brief Used to set echo pin.
    void setEcho(int Echo);

    //! \brief Function which triggers ultrasound pulse, reads echo pin, finds difference and returns distance in metres.
    float measureDistance();

    //! \brief Runs ultrasonic sensor routine
    static void run(Ultrasonic* ultrasonic);
    
    //! \brief Starts thread for ultrasonic sensor, checks its not already running
    void start();
    
    //! \brief Stops + tidies ultrasonic sensor thread.
    void stop();


};
#endif