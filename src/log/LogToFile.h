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
#include "ZGGLog.h"

class CLogToFile :public CZGGLog
{
public:
	typedef basic_string<TCHAR, char_traits<TCHAR>,
		allocator<TCHAR> > tstring;

	CLogToFile(){};

	BOOL InitLog(const TCHAR* strLogFileName = _T("ZggLog.log")/*Ĭ������*/,
					DWORD dwMaxOutputBufLen = 1024*1024 /*Ĭ�����1M�Ļ�����*/);

	BOOL WriteLog(const TCHAR* fmt,...);
private:

	HANDLE m_pFile;
	DWORD  m_dwMaxOutputBufLen;
	TCHAR*  m_pszOutputBuf;

};

#define  LOG_OUTPRINT CLogToFile::GetZggLogInstance()->WriteLog
