#pragma once
/**************************************************************************

Copyright:ZhuGege

Author: ZhuGege

Date:2016-03-13

Description:Inject DLL to Target Process

**************************************************************************/
#include <string>
#include <windows.h>
using namespace std;

class CZGGLog
{
private:
	string GetLogTime();
	bool InitLog(string strLogFileName);
	bool WriteInternal(string strLog);
private:
	FILE* m_pFile;

	//ÄÚ²¿Ëø
	class CLock
	{
	public:
#define ZGGLOG_LOCK_EVENT_NAME	_T("ZggLogLockEvent")
		
		CLock()
		{
			lock();
		}
		~CLock()
		{
			unlock();
		}

		void lock()
		{
			WaitForSingleObject(m_hEvent,INFINITE);
		}
		void unlock()
		{
			ResetEvent(m_hEvent);
		}
	private:
		static HANDLE m_hEvent;
	};
};