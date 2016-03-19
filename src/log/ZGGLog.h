#pragma once

/**************************************************************************

Copyright:ZhuGege

Author: ZhuGege

Date:2016-03-13

Description:abstract log

**************************************************************************/
#include <windows.h>
#include <string>
#include <tchar.h>

class CZGGLog
{
public:

	virtual BOOL GetLogTime(TCHAR* ptszLogTimeBuf, DWORD dwBufLen /*in tchar*/);

	virtual BOOL InitLog(const TCHAR* strLogFileName = _T("ZggLog.log")/*Ĭ������*/,
							DWORD dwMaxOutputBufLen = 1024*1024 /*Ĭ�����1M�Ļ�����*/) = 0;

	virtual BOOL WriteLog(const TCHAR* fmt,...) = 0;

	virtual void ConvertBufToHexMatrix(const void* pszSrcBuf, 
										DWORD dwSrcBufLen/*in bytes*/,
										std::string& strHexMatrix);

public:
	//�ڲ���
	class CLock
	{
	public:
#define ZGGLOG_LOCK_EVENT_NAME	_T("ZggLogLockEvent")

		CLock(){lock();}
		~CLock(){unlock();}
		void lock(){WaitForSingleObject(m_hEvent,INFINITE);}
		void unlock(){SetEvent(m_hEvent);}
	private:
		static HANDLE m_hEvent;
	};
};
