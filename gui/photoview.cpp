#include "photoview.h"
#include <QPixmap> 
#include <QImage>

PhotoViewer::PhotoViewer()
{
    /**
    * Adds the Photos as a label to the window
    */
        photo = new QLabel(this);
        QImage cameraimage("../Photos/compressed_birdcafe.jpg");
        QPixmap img = QPixmap::fromImage(cameraimage);
        photo->setPixmap(img);
        photo->setMinimumSize(400, 400);
    
        DispPhoto = new QVBoxLayout;
        DispPhoto->addWidget(photo);
        setLayout(DispPhoto);
}