/**************************************************************************

Copyright:ZhuGege

Author: ZhuGege

Date:2016-03-13

Description:Log To File Implement

**************************************************************************/

#include "LogToFile.h"
#include <time.h>
#include <tchar.h>


//***************************************************************
// Method:      InitLog
// FullName:    CLogToFile::InitLog
// Access:      public 
// Returns:     BOOL
// Qualifier:  
// Parameter:   const TCHAR * strLogFileName
// Parameter:   DWORD dwMaxOutputBufLen
// Description: 初始化日志
//***************************************************************
BOOL ZGG::CLogToFile::InitLog(__in const TCHAR* strLogFileName /*= _T("ZggLog.log")默认名称*/, 
							  __in DWORD dwMaxOutputBufLen /*= 1024*1024 默认最大1M的缓冲区*/)
{
	
	m_pFile = CreateFile(strLogFileName,
							FILE_WRITE_DATA|FILE_READ_DATA,
							FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
							NULL,OPEN_ALWAYS,
							FILE_ATTRIBUTE_NORMAL,
							NULL);

	if (m_pFile != INVALID_HANDLE_VALUE)
	{
		//移动文件尾部，附加
		SetFilePointer(m_pFile, 0, NULL, FILE_END); 
		//设置最大缓冲区
		m_dwMaxOutputBufLen = dwMaxOutputBufLen;
		//申请空间
		m_pszOutputBuf = new(std::nothrow) TCHAR[m_dwMaxOutputBufLen];
	}

	return (m_pFile != INVALID_HANDLE_VALUE) && (m_pszOutputBuf != NULL);

}

//***************************************************************
// Method:      WriteLog
// FullName:    CLogToFile::WriteLog
// Access:      public 
// Returns:     BOOL
// Qualifier:  
// Parameter:   const TCHAR * fmt
// Parameter:   ...
// Description: 写日志
//***************************************************************
BOOL ZGG::CLogToFile::WriteLog(__in const TCHAR* fmt,...)
{
	if (m_pFile == INVALID_HANDLE_VALUE || m_pszOutputBuf == NULL)
	{
		return FALSE;
	}

	RtlZeroMemory(m_pszOutputBuf,m_dwMaxOutputBufLen * sizeof(TCHAR));
	va_list args; 
	va_start(args, fmt);				
	_vstprintf_s(m_pszOutputBuf, m_dwMaxOutputBufLen,fmt, args);

	tstring strWrite;
	TCHAR tszLogTime[21] = {0};
	GetLogTime(tszLogTime,_countof(tszLogTime));
	
	strWrite.assign(tszLogTime);
	strWrite.append(_T("  "));
	strWrite.append(m_pszOutputBuf);
	strWrite.append(_T("\r\n"));

	//lock for multithread
	CLock lock;

	DWORD dwRet;
	return WriteFile(m_pFile,strWrite.c_str(),strWrite.length()*sizeof(TCHAR),&dwRet,NULL);
}
