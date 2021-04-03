//Joe Costello
//16/02
//Camera Driver
//adapted from: 

/**********************************************************
 Software developed by AVA ( Ava Group of the University of Cordoba, ava  at uco dot es)
 Main author Rafael Munoz Salinas (rmsalinas at uco dot es)
 This software is released under BSD license as expressed below
-------------------------------------------------------------------
Copyright (c) 2013, AVA ( Ava Group University of Cordoba, ava  at uco dot es)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:

   This product includes software developed by the Ava group of the University of Cordoba.

4. Neither the name of the University nor the names of its contributors
   may be used to endorse or promote products derived from this software
   without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY AVA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL AVA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
****************************************************************/
//!**************************************************************
//! \file
//! \brief Runs driver operations
//!**************************************************************

#include <ctime>
#include <raspicam/raspicam.h>
#include "BirdCam.h"
#include "USsensor.h"
#include <wiringPi.h>
#include <thread>
#include <stdio.h>

using namespace std;

const int trig = 18;
const int echo = 24;

//! @brief Configures the camera settings - adapted from code in 'raspicam_test.cpp' by Ava Group, University of Cordoba 
//! found here: https://github.com/cedricve/raspicam/blob/c4c0dc10d32980fdbd6adb20aa439054ce8b00fd/utils/raspicam_test.cpp
void camStandardConfig( raspicam::RaspiCam *Camera )
{
    Camera->setWidth (1280); 
    Camera->setHeight (960); 
    Camera->setBrightness (55);

    Camera->setSharpness (0);
    Camera->setContrast (0);
    Camera->setSaturation (5);
    Camera->setShutterSpeed(0);
    Camera->setISO (800);
    Camera->setFrameRate(30);
    Camera->setVideoStabilization ( true );
    Camera->setExposureCompensation (0);

    Camera->setAWB_RB(1,1);
}


int main ( int argc,char **argv ) {
   wiringPiSetupGpio(); 
   Ultrasonic *cam1 = new Ultrasonic(trig, echo);
   camStandardConfig(cam1);
   cam1->setFilePath("../../Photos/birdcafe.ppm");
   cam1->start();
   getchar();
   cam1->stop();
   delete cam1;

   return 0;
}