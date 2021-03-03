#ifndef WINDOW_H
#define WINDOW_H
#include <QWindow>
#include <QPushButton>
//#include <QLayout>
#include <QBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QProcess>
#include<QDebug>

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
	//void qInfo();
	//bool setAlignment();

// internal variables for the window class
private:
    QPushButton *startbutton;
    QPushButton *stopbutton;
    QLabel *title;
	QLabel *icon;
	QProcess *process;
	
    

	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QVBoxLayout  *vLayout;  // vertical layout
	QHBoxLayout  *hLayout;  // horizontal layout

};

#endif // WINDOW_H