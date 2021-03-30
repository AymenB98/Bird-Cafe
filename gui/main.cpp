#include "window.h"
#include "photoview.h"

#include <QApplication>

// Main program
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	// create the window
	Window window;
	window.show();
	window.setMinimumSize(1,1);
	//window.setFixedSize(800,800);
	PhotoViewer photoviewer;
	//photoviewer.show();
	// execute the application
	return app.exec();
}