#include "CRecvMsgThread.h"
#include <Windows.h>
#include <QFile>
#include <QTextStream>

#pragma pack(push)
#pragma pack(1)
typedef struct __DEBUGBUFFER
{
	DWORD sz;
	char szString[4096 - sizeof(DWORD)]; //这里保存了OutputDebugString输出的字符串
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
	// 设置初始结果
	m_dwResult = ERROR_INVALID_HANDLE;
	// 打开事件句柄
	hAckEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("DBWIN_BUFFER_READY"));
	m_hReadyEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("DBWIN_DATA_READY"));
	// 创建文件映射
	hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 4096, TEXT("DBWIN_BUFFER"));
	// 映射调试缓冲区
	pdbBuffer = (PDEBUGBUFFER)MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
	// 循环
	for (m_dwResult = ERROR_SIGNAL_PENDING; (m_dwResult == ERROR_SIGNAL_PENDING);)
	{
		// 等待缓冲区数据
		SetEvent(hAckEvent);
		if (WaitForSingleObject(m_hReadyEvent, INFINITE) == WAIT_OBJECT_0)
		{
			// 如果是继续等待，否则表示主线程发出了停止信号，退出当前线程
			if (m_dwResult == ERROR_SIGNAL_PENDING)
			{ 
				// 添加新项
				printf(pdbBuffer->szString);
				emit push_msg(pdbBuffer->szString);
			}
		}
		else
		{
			// 等待失败
			m_dwResult = WAIT_ABANDONED;
		}
	}
	{
		// 释放
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
