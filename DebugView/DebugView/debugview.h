#ifndef DEBUGVIEW_H
#define DEBUGVIEW_H

#include <QtGui/QMainWindow>
#include "ui_debugview.h"
#include "CRecvMsgThread.h"

class DebugView : public QMainWindow
{
	Q_OBJECT

public:
	DebugView(QWidget *parent = 0, Qt::WFlags flags = 0);
	~DebugView();

private:
	Ui::DebugViewClass ui;
	CRecvMsgThread m_recvMsgThrd;

private slots:
	void on_pushButtonStart_clicked();
	void on_pushButtonClear_clicked();
	void on_recvMsgTrhd_push_msg(QString msg);
};

#endif // DEBUGVIEW_H
