#include "window.h"
#include <QPixmap>

Window::Window() 
{
    //window->setGeometry(QRect(QPoint(300, 300), QSize(2000, 500)));
    icon = new QLabel(this);
    QPixmap pic("/home/pi/projects/gui_qt_tests/GUI/bird_logo_pink.jpg");
    icon->setPixmap(pic);
    //icon->setAlignment(Qt::AlignCentre);

    title = new QLabel(this);
    title->setText("Welcome to the Bird Cafe");
    //title->setAlignment(Qt::AlignCentre);
    
    startbutton = new QPushButton("Start", this);
     startbutton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
     connect(startbutton, &QPushButton::clicked, this, &Window::handleStartButton);

    stopbutton = new QPushButton("Stop", this);
     stopbutton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
	 connect(stopbutton, &QPushButton::clicked, this, &Window::handleStopButton);

	// set up the layout - knob above thermometer
	vLayout = new QVBoxLayout;
    vLayout->addWidget(icon);
    vLayout->addWidget(title);
	vLayout->addWidget(startbutton);
	vLayout->addWidget(stopbutton);

    setLayout(vLayout);

}

   void Window::handleStartButton(){
       
//qInfo is qt5.5+ only.
    qInfo() << "Start Button Pressed, taking photo";
    //currently functional
    process = new QProcess(this);
    process->start("/home/pi/projects/BirdCafe/Bird-Cafe/drivers/build/birdcafe_raspicam");
    process->waitForStarted();
    process->waitForFinished();
    process->close();
    qInfo() << "Photo taken, see birdcafe.ppm";

    }

       void Window::handleStopButton(){
       
//qInfo is qt5.5+ only.
    qInfo() << "Stop Button Pressed, no action taken";
    
    }
