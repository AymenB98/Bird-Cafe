#include "photoview.h"
#include <QPixmap> 

/**
 * The code for the photo viewer window
*/

PhotoViewer::PhotoViewer()
{
    /**
    * Adds the Photos as a label to the window
    */
        photo = new QLabel(this);
        QPixmap pic("../Photos/birdcafe.ppm");
        photo->setPixmap(pic);
        photo->setMinimumSize(1, 1);
    
        DispPhoto = new QVBoxLayout;
        DispPhoto->addWidget(photo);
        setLayout(DispPhoto);
}