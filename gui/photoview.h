#ifndef PHOTOVIEW_H
#define PHOTOVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QBoxLayout>


class PhotoViewer : public QWidget
{
    Q_OBJECT

public:
	PhotoViewer();

private:
	QLabel *photo;
	QVBoxLayout *DispPhoto;

};

#endif //PHOTOVIEW_H
