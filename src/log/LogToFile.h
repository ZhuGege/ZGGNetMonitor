#pragma once
/**************************************************************************

Copyright:ZhuGege

Author: ZhuGege

Date:2016-03-13

Description:Log To File Implement

**************************************************************************/
#include <string>
#include <windows.h>
using namespace std;
#include "Log.h"

namespace ZGG
{

class CLogToFile :public CLog
{
public:
	typedef basic_string<TCHAR, char_traits<TCHAR>,
		allocator<TCHAR> > tstring;

	CLogToFile(__in const TCHAR* ptszLogFileName = _T("ZggLog.log")/*默认名称*/,
			   __in DWORD dwMaxOutputBufLen = 1024*1024 /*默认最大1M的缓冲区*/)
	{	
		m_pFile = INVALID_HANDLE_VALUE;
		m_dwMaxOutputBufLen = dwMaxOutputBufLen;
		m_pszOutputBuf = NULL;
		RtlZeroMemory(m_tszLogFileName,_countof(m_tszLogFileName)*sizeof(TCHAR));
		RtlCopyMemory(m_tszLogFileName,ptszLogFileName,min(_tcslen(ptszLogFileName),_countof(m_tszLogFileName))*sizeof(TCHAR));
	}

	BOOL InitLog();

	BOOL WriteLog(__in const TCHAR* fmt,...);
private:

	HANDLE m_pFile;
	DWORD  m_dwMaxOutputBufLen;
	TCHAR* m_pszOutputBuf;
	TCHAR  m_tszLogFileName[MAX_PATH];

};


} //namespace ZGG