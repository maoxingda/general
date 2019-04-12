#include "debugview.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DebugView w;
	w.show();
	return a.exec();
}
