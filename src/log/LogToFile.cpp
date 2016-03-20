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
// FullName:    ZGG::CLogToFile::InitLog
// Access:      public 
// Returns:     BOOL
// Qualifier:  
// Description: 创建日志
//***************************************************************
BOOL ZGG::CLogToFile::InitLog()
{
	
	m_pFile = CreateFile(m_tszLogFileName,
							FILE_WRITE_DATA|FILE_READ_DATA,
							FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
							NULL,OPEN_ALWAYS,
							FILE_ATTRIBUTE_NORMAL,
							NULL);

	if (m_pFile != INVALID_HANDLE_VALUE)
	{
		//移动文件尾部，附加
		SetFilePointer(m_pFile, 0, NULL, FILE_END); 
	}

	return (m_pFile != INVALID_HANDLE_VALUE);

}



//***************************************************************
// Method:      WriteLog
// FullName:    ZGG::CLogToFile::WriteLog
// Access:      public 
// Returns:     BOOL
// Qualifier:  
// Parameter:   __in const void * ptszOutputBuf
// Parameter:   __in DWORD dwOutputBufLen
// Description: 输出
//***************************************************************
BOOL ZGG::CLogToFile::WriteLog(__in const void* ptszOutputBuf ,__in DWORD dwOutputBufLen /*in bytes*/)
{
	if (m_pFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	DWORD dwRet;
	return WriteFile(m_pFile,ptszOutputBuf,dwOutputBufLen,&dwRet,NULL);
}
