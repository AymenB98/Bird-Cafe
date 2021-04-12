
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
//! \brief Header file for BirdCam subclass
//!**************************************************************

#ifndef _BIRDCAM_H
#define _BIRDCAM_H


#include <raspicam/raspicam.h>
#include <string>
#include <fstream>
#include <iostream>
#include <ostream>
#include <ctime>
#include <experimental/filesystem>

//! Class used for interfacing with pi camera - subclass of RaspiCam
class BirdCam : public raspicam::RaspiCam 
{//class used for interfacing pi camera
private: 
   
   std::string FilePath; //set to filepath of photos taken with BirdCam
   
   //! Checks if a user-given file path exists, returns true if yes, false if no.
   //! @param[in] filePath
   bool checkFilePathExists(std::string filePath);

public:

   //setters
   //! Sets file path to which captured photos are saved.
   //! @param[in] filePath
   void setFilePath(std::string filePath);

   //getters
   //! Gets filepath of photos taken.
   //! @param[out] FilePath
   std::string getFilePath();

   
  //! \brief Function which takes a photograph when called. 
  //! Photograph saved to path set by setFilePath().
   void takePhoto(); //function to take photo

};

#endif