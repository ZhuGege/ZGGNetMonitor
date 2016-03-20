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

	virtual BOOL InitLog() = 0;

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
		void lock()
		{
			if (m_hEvent == NULL)
			{
				do 
				{	//创建一个新的同步事件
					TCHAR tszEventName[50]= {0};
					static DWORD dwIndex = 1;
					_stprintf_s(tszEventName,_countof(tszEventName),_T("%s%d"),ZGGLOG_LOCK_EVENT_NAME,dwIndex++);
					m_hEvent = CreateEvent(NULL,TRUE,TRUE,tszEventName);
				} while (GetLastError() == ERROR_ALREADY_EXISTS || m_hEvent == NULL);
			}
			WaitForSingleObject(m_hEvent,INFINITE);
		}
		void unlock(){SetEvent(m_hEvent);}
	private:
		static HANDLE m_hEvent;
	};
};

}//namespace ZGG