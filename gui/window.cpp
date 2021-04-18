#include "window.h"
#include "photoview.h"
//#include "../drivers/latencyTimers.h"
#include <QPixmap>
#include <fstream>

/**
 * Code to create the Main Window for SmartBirdCafe GUI
 */

FILE* guiStartLog = fopen("GUI_start_log.dat", "at");
FILE* guiStopLog = fopen("GUI_stop_log.dat", "at");
FILE* guiPhotoLog = fopen("GUI_photo_log.dat", "at");

float startButtonDuration;
float stopButtonDuration;
float photoDuration;

//! Creates the main window of Smart Bird Cafe, holding three buttons
Window::Window() 
{
    /**
    * This created the 3 buttons and the icon for the Main Window 
    */
    icon = new QLabel(this); 
    QPixmap pic("./bird_logo_pink.jpg");
    icon->setPixmap(pic);
    

    title = new QLabel(this);
    title->setText("Welcome to the Bird Cafe");
    
    startbutton = new QPushButton("Start", this);
     startbutton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
     connect(startbutton, &QPushButton::clicked, this, &Window::handleStartButton);

    stopbutton = new QPushButton("Stop", this);
     stopbutton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
	 connect(stopbutton, &QPushButton::clicked, this, &Window::handleStopButton);
    
    photoviewerbutton = new QPushButton("View Photos", this);
     photoviewerbutton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
	 connect(photoviewerbutton, &QPushButton::clicked, this, &Window::handlePhotoViewer);

	// set up the layout - knob above thermometer
	vLayout = new QVBoxLayout;
    vLayout->addWidget(icon);
    vLayout->addWidget(title);
	vLayout->addWidget(startbutton);
	vLayout->addWidget(stopbutton);
    vLayout->addWidget(photoviewerbutton);

    setLayout(vLayout);

}

//! Takes the signal from the start button and starts the external camera code, disables start button to prevent errors
void Window::handleStartButton()
{
    
    std::chrono::high_resolution_clock::time_point startButtonStart = std::chrono::high_resolution_clock::now();
    process = new QProcess(this);
    process->start("../drivers/build/birdcafe_raspicam");
    process->waitForStarted();

    std::chrono::high_resolution_clock::time_point startButtonStop = std::chrono::high_resolution_clock::now(); 
    startButtonDuration = std::chrono::duration <float> (startButtonStop - startButtonStart).count();
    fprintf(guiStartLog, "%f\n", 1000*startButtonDuration); 

    startbutton->setText("Camera on");
    startbutton->setEnabled(false);

}

//! Takes the signal from the stop button and stops the external camera code, re-enables start button
void Window::handleStopButton()
{
    /**
    * Takes the signal from the stop button and stops the external camera code, reenables start button
    */
    std::chrono::high_resolution_clock::time_point stopButtonStart = std::chrono::high_resolution_clock::now();
    process->close();

    std::chrono::high_resolution_clock::time_point stopButtonStop = std::chrono::high_resolution_clock::now(); 
    stopButtonDuration = std::chrono::duration <float> (stopButtonStop - stopButtonStart).count();
    fprintf(guiStopLog, "%f\n", 1000*stopButtonDuration);
 

    startbutton->setEnabled(true);
    startbutton->setText("Start");
}

//! Takes the signal from the "View Photos" button and opens a seperate window with the most recent photo in it
void Window::handlePhotoViewer()
{
    /**
    * Opens the photos taken by the camera in a new window
    */
    std::chrono::high_resolution_clock::time_point photoStart = std::chrono::high_resolution_clock::now(); 
    PV = new PhotoViewer();
    PV->show();

    std::chrono::high_resolution_clock::time_point photoStop = std::chrono::high_resolution_clock::now(); 
    photoDuration = std::chrono::duration <float> (photoStop - photoStart).count();
    fprintf(guiPhotoLog, "%f\n", 1000*photoDuration);

}