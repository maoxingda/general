#include "debugviewdemo.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DebugViewDemo w;
	w.show();
	return a.exec();
}
