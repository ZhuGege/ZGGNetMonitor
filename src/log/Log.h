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

namespace ZGG
{

class CLog
{
public:

	virtual BOOL GetLogTime(__out TCHAR* ptszLogTimeBuf, __in DWORD dwBufLen /*in tchar*/);

	virtual BOOL InitLog(__in const TCHAR* strLogFileName = _T("ZggLog.log")/*默认名称*/,
							__in DWORD dwMaxOutputBufLen = 1024*1024 /*默认最大1M的缓冲区*/) = 0;

	virtual BOOL WriteLog(__in const TCHAR* fmt,...) = 0;

	virtual void ConvertBufToHexMatrix(__in const void* pszSrcBuf, 
										__in DWORD dwSrcBufLen/*in bytes*/,
										__out std::string& strHexMatrix);

public:
	//内部锁
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

}//namespace ZGG