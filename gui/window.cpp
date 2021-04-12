#include "window.h"
#include "photoview.h"
#include <QPixmap>

/**
 * Code to create the Main Window for SmartBirdCafe GUI
 */

Window::Window() 
{
    /**
    * This created the 3 buttons and the icon for the Main Window 
    */
    icon = new QLabel(this); 
    QPixmap pic("/home/pi/projects/gui_qt_tests/GUI/bird_logo_pink.jpg");
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

	// set up the layout - icon then title then two buttons
	vLayout = new QVBoxLayout;
    vLayout->addWidget(icon);
    vLayout->addWidget(title);
	vLayout->addWidget(startbutton);
	vLayout->addWidget(stopbutton);
    vLayout->addWidget(photoviewerbutton);

    setLayout(vLayout);

}

void Window::handleStartButton()
{
    /**
    * Takes the signal from the start button and starts the external camera code, disables start button to prevent errors
    */
    process = new QProcess(this);
    process->start("/home/pi/projects/BirdCafe/Bird-Cafe/drivers/build/birdcafe_raspicam");
    process->waitForStarted();
    startbutton->setText("Camera on");
    startbutton->setEnabled(false);

}

void Window::handleStopButton()
{
    /**
    * Takes the signal from the stop button and stops the external camera code, reenables start button
    */
    process->close();
    startbutton->setEnabled(true);
    startbutton->setText("Start");
}

void Window::handlePhotoViewer()
{
    /**
    * Opens the photos taken by the camera in a new window
    */
        PV = new PhotoViewer();
        PV->show();
        PV->adjustSize();

}
