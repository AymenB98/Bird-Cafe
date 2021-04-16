#include "window.h"
#include "photoview.h"
//#include "../drivers/latencyTimers.h"
#include <QPixmap>

/**
 * Code to create the Main Window for SmartBirdCafe GUI
 */


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
    
    std::chrono::steady_clock::time_point startButtonPress = std::chrono::steady_clock::now(); 
    process = new QProcess(this);
    process->start("../drivers/build/birdcafe_raspicam");
    process->waitForStarted();
    std::chrono::steady_clock::time_point processStarted = std::chrono::steady_clock::now(); 
    startbutton->setText("Camera on");
    startbutton->setEnabled(false);
    float processStartDuration = std::chrono::duration <float> (processStarted - startButtonPress).count();

    qInfo("Latency for Button push to process start : %f ms\n", 1000*processStartDuration); 

}

//! Takes the signal from the stop button and stops the external camera code, re-enables start button
void Window::handleStopButton()
{
    /**
    * Takes the signal from the stop button and stops the external camera code, reenables start button
    */
    std::chrono::steady_clock::time_point stopButtonPress = std::chrono::steady_clock::now(); 
    process->close();
    std::chrono::steady_clock::time_point processEnded = std::chrono::steady_clock::now(); 
    float processStopDuration = std::chrono::duration <float> (processEnded - stopButtonPress).count();
    qInfo("Latency for Button push to process end : %f ms\n", 1000*processStopDuration); 
    startbutton->setEnabled(true);
    startbutton->setText("Start");
}

//! Takes the signal from the "View Photos" button and opens a seperate window with the most recent photo in it
void Window::handlePhotoViewer()
{
    /**
    * Opens the photos taken by the camera in a new window
    */
    std::chrono::steady_clock::time_point PVButtonPress = std::chrono::steady_clock::now(); 
    PV = new PhotoViewer();
    PV->show();
    std::chrono::steady_clock::time_point PVOpen = std::chrono::steady_clock::now(); 
    float PVLoad = std::chrono::duration <float> (PVOpen - PVButtonPress).count();
    qInfo("Latency for Button push to open photo viewer : %f ms\n", 1000*PVLoad); 

}