#ifndef WINDOW_H
#define WINDOW_H
#include "photoview.h"
#include <QWindow>
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QProcess>
#include <QDebug>
#include <QKeyEvent>
#include <QCoreApplication>


extern float processStartDuration;
extern float startButtonPress;
extern float processStarted;

extern float processStopDuration;
extern float stopButtonPress;
extern float processEnded;

extern float PVLoad;
extern float PVButtonPress;
extern float PVOpen;

// class definition 'Window'
class Window : public QWidget
{
	// must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
	Q_OBJECT

public:
	Window(); // default constructor - called when a Window is declared without arguments

private slots:
	void handleStartButton();
	void handleStopButton();
	void handlePhotoViewer();
	//void qInfo();
	

// internal variables for the window class
private:
    QPushButton *startbutton;
    QPushButton *stopbutton;
	QPushButton *photoviewerbutton;
    QLabel *title;
	QLabel *icon;
	QProcess *process;
	PhotoViewer *PV;
	

	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QVBoxLayout  *vLayout;  // vertical layout
	QHBoxLayout  *hLayout;  // horizontal layout

};


#endif // WINDOW_H