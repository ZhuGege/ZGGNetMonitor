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

	CLogToFile(){	
		m_pFile = INVALID_HANDLE_VALUE;
		m_dwMaxOutputBufLen = 0;
		m_pszOutputBuf = NULL;
	}

	BOOL InitLog(__in const TCHAR* strLogFileName = _T("ZggLog.log")/*默认名称*/,
				 __in DWORD dwMaxOutputBufLen = 1024*1024 /*默认最大1M的缓冲区*/);

	BOOL WriteLog(__in const TCHAR* fmt,...);
private:

	HANDLE m_pFile;
	DWORD  m_dwMaxOutputBufLen;
	TCHAR*  m_pszOutputBuf;

};


} //namespace ZGG