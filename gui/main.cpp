#include "window.h"

#include <QApplication>

// Main program
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	// create the window
	Window window;
	window.show();
	//window.setFixedSize(800,800);
    

	// execute the application
	return app.exec();
}