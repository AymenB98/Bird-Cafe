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
        
    float distanceCalcUS(float pulseTime);
    
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