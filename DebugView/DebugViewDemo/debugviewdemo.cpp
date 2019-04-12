#include "debugviewdemo.h"
#include <Windows.h>

DebugViewDemo::DebugViewDemo(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
}

DebugViewDemo::~DebugViewDemo()
{

}

void DebugViewDemo::on_pushButtonLog_clicked()
{
	OutputDebugStringA("123");
}
