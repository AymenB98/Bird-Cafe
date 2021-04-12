
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
//! \brief Defines BirdCam subclass
//!**************************************************************

#include "BirdCam.h"
namespace fs = std::experimental::filesystem;

//setters
void BirdCam::setFilePath(std::string filePath)
{
   FilePath = filePath;
}

//getters
std::string BirdCam::getFilePath()
{
   return FilePath;
}

bool BirdCam::checkFilePathExists(std::string filePath) //not yet implemented - remember to edit the cmake
{
   fs::path p = filePath;
   if(fs::exists(p))
   {
      return true;
   }
   else
   {
      return false;
   }
}

void BirdCam::takePhoto()
{
   std::cout<<"Opening Camera..."<<std::endl;
   if ( !raspicam::RaspiCam::open()) //checks if camera available
   {
      std::cerr << "Error opening camera" << std::endl;
   }
    //capture
   std::cout<< "Capturing Image..." << std::endl;
   raspicam::RaspiCam::grab();
   //allocate memory
   unsigned char *data=new unsigned char[raspicam::RaspiCam::getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB )];
   //extract the image in rgb format
   raspicam::RaspiCam::retrieve(data);//get camera image
   //save
   if (FilePath.empty()) //if no filepath set, default to birdcafe.ppm in local, throw warning.
   {
      FilePath = "birdcafe.ppm";
      std::cerr << "WARNING: No file path set, picture will be saved in local directory." <<std::endl << "Set a file path using BirdCam::setFilePath()." <<std::endl;
   }
   std::ofstream outFile(FilePath, std::ios::binary); 
   outFile<<"P6\n"<<raspicam::RaspiCam::getWidth() <<" "<<raspicam::RaspiCam::getHeight() <<" 255\n";
   outFile.write ( ( char* ) data, raspicam::RaspiCam::getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ) );
   if (checkFilePathExists(FilePath) == false) 
   {
      std::cerr << "ERROR: Filepath: " << FilePath << " does not exist." << std::endl << "Filepath has been set to /birdcafe.ppm" << std::endl;
      FilePath = "birdcafe.ppm"; //If non-existant filepath given, default to local directory, named birdcafe.ppm
      std::ofstream outFile(FilePath, std::ios::binary); 
      outFile<<"P6\n"<<raspicam::RaspiCam::getWidth() <<" "<<raspicam::RaspiCam::getHeight() <<" 255\n";
      outFile.write ( ( char* ) data, raspicam::RaspiCam::getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ) );
   }
   std::cout<<"Image saved at " << FilePath <<std::endl;
   raspicam::RaspiCam::release();
   delete data;

}

/*bool checkFilePathExists(std::string filePath) //not yet implemented - remember to edit the cmake
{
   fs::path p = filePath;
   if(fs::exists(p))
   {
      return true;
   }
   else
   {
      std::cerr << "ERROR: Filepath: " << filePath << " does not exist. Filepath has been set to /defaultBird.ppm" << std::endl;
      std::string d = "defaultBird.ppm";
      return false;
   }
}
*/