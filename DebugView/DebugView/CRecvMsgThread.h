#ifndef CRECVMSGTHREAD_H
#define CRECVMSGTHREAD_H

#include <QThread>

class CRecvMsgThread : public QThread
{
	Q_OBJECT

public:
	CRecvMsgThread(QObject *parent = 0);
	~CRecvMsgThread();

signals:
	void push_msg(QString msg);
	
protected:
	virtual void run();

};

#endif // CRECVMSGTHREAD_H
