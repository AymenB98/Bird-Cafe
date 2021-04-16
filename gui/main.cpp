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
	window.setMinimumSize(400,400);
	PhotoViewer photoviewer;
	// execute the application
	return app.exec();
}