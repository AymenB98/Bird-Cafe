//!**************************************************************
//! \file
//! \brief Defines Ultrasonic subclass
//!**************************************************************

#include "USsensor.h"

float Ultrasonic::distanceCalcUS(float pulseTime)
{
    float pulseDist = (pulseTime*speed_of_sound)/2;
    return pulseDist;
}

float Ultrasonic::measureDistance()
{
    digitalWrite(trig, LOW); //trigger pin low for 2us, clears pin
    delayMicroseconds(2);
    digitalWrite(trig, HIGH); //trigger pin high for 10us to send pulse
    delayMicroseconds(10);
    digitalWrite(trig, LOW); //trigger pin low to end 10us pulse
    
    while (digitalRead(echo) == LOW)
    {
        // wait until echo pin HIGH (receives echo)
    }
    std::chrono::steady_clock::time_point timerStart = std::chrono::steady_clock::now(); //start timer
    while (digitalRead(echo) == HIGH)
    {
        //wait while echo pin High
    }
    std::chrono::steady_clock::time_point timerStop = std::chrono::steady_clock::now(); //stop timer

    float pulseDur = std::chrono::duration<float>(timerStop-timerStart).count(); //force timer to float
    float distance = distanceCalcUS(pulseDur);
    std::cout << distance << std::endl;

    return distance;
}

void Ultrasonic::setTrigger(int Trig)
{
    trig = Trig;
}

void Ultrasonic::setEcho(int Echo)
{
    echo = Echo;
}

void Ultrasonic::start()
{
    if (USThread)
    {
        throw "ERROR: Thread already running.";
    }
        USThread = new std::thread(run, this);
}

void Ultrasonic::stop()
{
    running = 0;
    if (USThread)
    {
        USThread->join();
        delete USThread;
        USThread = NULL;
    }
}

void Ultrasonic::run(Ultrasonic* ultrasonic)
{
    ultrasonic->running =1;
    while (ultrasonic->running)
    {
        if(ultrasonic->measureDistance() < 1.0)
        {
            if(ultrasonic->measureDistance() < 1.0)
            {
                if(ultrasonic->measureDistance() < 1.0) //3 quick checks to lower error chance
                {
                    ultrasonic->takePhoto();
                    std::this_thread::sleep_for(std::chrono::seconds(30));
                }
            }  
        }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}