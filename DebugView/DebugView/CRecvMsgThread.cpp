#include "CRecvMsgThread.h"
#include <Windows.h>
#include <QFile>
#include <QTextStream>

#pragma pack(push)
#pragma pack(1)
typedef struct __DEBUGBUFFER
{
	DWORD sz;
	char szString[4096 - sizeof(DWORD)]; //���ﱣ����OutputDebugString������ַ���
} DEBUGBUFFER, *PDEBUGBUFFER;
#pragma pack(pop)

CRecvMsgThread::CRecvMsgThread(QObject *parent)
	: QThread(parent)
{

}

CRecvMsgThread::~CRecvMsgThread()
{

}

void CRecvMsgThread::run()
{
	QFile f("d:/debug_view.log");
	f.open(QIODevice::Append);
	QTextStream ts(&f);
	HANDLE m_hReadyEvent;
	DWORD m_dwResult;
	HANDLE hMapping = NULL;
	HANDLE hAckEvent = NULL;
	PDEBUGBUFFER pdbBuffer = NULL;
	// ���ó�ʼ���
	m_dwResult = ERROR_INVALID_HANDLE;
	// ���¼����
	hAckEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("DBWIN_BUFFER_READY"));
	m_hReadyEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("DBWIN_DATA_READY"));
	// �����ļ�ӳ��
	hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 4096, TEXT("DBWIN_BUFFER"));
	// ӳ����Ի�����
	pdbBuffer = (PDEBUGBUFFER)MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
	// ѭ��
	for (m_dwResult = ERROR_SIGNAL_PENDING; (m_dwResult == ERROR_SIGNAL_PENDING);)
	{
		// �ȴ�����������
		SetEvent(hAckEvent);
		if (WaitForSingleObject(m_hReadyEvent, INFINITE) == WAIT_OBJECT_0)
		{
			// ����Ǽ����ȴ��������ʾ���̷߳�����ֹͣ�źţ��˳���ǰ�߳�
			if (m_dwResult == ERROR_SIGNAL_PENDING)
			{ 
				// �������
				printf(pdbBuffer->szString);
				emit push_msg(pdbBuffer->szString);
			}
		}
		else
		{
			// �ȴ�ʧ��
			m_dwResult = WAIT_ABANDONED;
		}
	}
	{
		// �ͷ�
		if (pdbBuffer)
		{
			UnmapViewOfFile(pdbBuffer);
		}
		CloseHandle(hMapping);
		CloseHandle(m_hReadyEvent);
		CloseHandle(hAckEvent);
		f.close();
	}
}
