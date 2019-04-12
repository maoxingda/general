#include "debugview.h"

DebugView::DebugView(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
}

DebugView::~DebugView()
{

}

void DebugView::on_pushButtonStart_clicked()
{
	connect(&m_recvMsgThrd, SIGNAL(push_msg(QString)), SLOT(on_recvMsgTrhd_push_msg(QString)));
	m_recvMsgThrd.start();
}

void DebugView::on_pushButtonClear_clicked()
{
	ui.listWidget->clear();
}

void DebugView::on_recvMsgTrhd_push_msg(QString msg)
{
	ui.listWidget->addItem(msg);
}
