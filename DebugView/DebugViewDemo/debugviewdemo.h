#ifndef DEBUGVIEWDEMO_H
#define DEBUGVIEWDEMO_H

#include <QtGui/QMainWindow>
#include "ui_debugviewdemo.h"

class DebugViewDemo : public QMainWindow
{
	Q_OBJECT

public:
	DebugViewDemo(QWidget *parent = 0, Qt::WFlags flags = 0);
	~DebugViewDemo();

private:
	Ui::DebugViewDemoClass ui;

private slots:
	void on_pushButtonLog_clicked();
};

#endif // DEBUGVIEWDEMO_H
