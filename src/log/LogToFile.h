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

	CLogToFile(__in const TCHAR* ptszLogFileName = _T("ZggLog.log")/*Ä¬ÈÏÃû³Æ*/)
	{	
		m_pFile = INVALID_HANDLE_VALUE;
		RtlZeroMemory(m_tszLogFileName,_countof(m_tszLogFileName)*sizeof(TCHAR));
		RtlCopyMemory(m_tszLogFileName,ptszLogFileName,min(_tcslen(ptszLogFileName),_countof(m_tszLogFileName))*sizeof(TCHAR));
	}

	BOOL InitLog();
	BOOL WriteLog(__in const void* ptszOutputBuf ,__in DWORD dwOutputBufLen /*in bytes*/);
private:

	HANDLE m_pFile;
	TCHAR  m_tszLogFileName[MAX_PATH];

};


} //namespace ZGG