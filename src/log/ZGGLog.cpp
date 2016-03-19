/**************************************************************************

Copyright:ZhuGege

Author: ZhuGege

Date:2016-03-13

Description:abstract log

**************************************************************************/

#include "ZGGLog.h"
#include <time.h>

HANDLE CZGGLog::CLock::m_hEvent = CreateEvent(NULL,TRUE,TRUE,ZGGLOG_LOCK_EVENT_NAME);

//***************************************************************
// Method:      GetLogTime
// FullName:    CZGGLog::GetLogTime
// Access:      virtual public 
// Returns:     BOOL
// Qualifier:  
// Parameter:   TCHAR * ptszLogTimeBuf
// Parameter:   DWORD dwBufLen ,in tchar
// Description: 获取当前时间
//***************************************************************
BOOL CZGGLog::GetLogTime(TCHAR* ptszLogTimeBuf, DWORD  dwBufLen/*in tchar*/)
{
	if (ptszLogTimeBuf == NULL || dwBufLen == 0)
	{
		return FALSE;
	}

	time_t stLogTime;
	TCHAR tszLogTime[21] = {0};

	time(&stLogTime);
	struct tm tm_info;

	localtime_s(&tm_info,&stLogTime);
	_tcsftime(tszLogTime, _countof(tszLogTime), _T("%Y-%m-%d %H:%M:%S"),&tm_info );

	RtlCopyMemory(ptszLogTimeBuf,tszLogTime,min(dwBufLen,_countof(tszLogTime))*sizeof(TCHAR));

	return TRUE;
}

//***************************************************************
// Method:      ConvertBufToHexMatrix
// FullName:    CZGGLog::ConvertBufToHexMatrix
// Access:      virtual public 
// Returns:     void
// Qualifier:  
// Parameter:   const void * pszSrcBuf
// Parameter:   DWORD dwSrcBufLen
// Parameter:   void * pszDestBuf
// Parameter:   DWORD dwDestBufLen
// Description: 将字符串转换为十六进制矩阵
//***************************************************************
void CZGGLog::ConvertBufToHexMatrix(const void* pszSrcBuf, DWORD dwSrcBufLen/*in bytes*/,
									std::string& strHexMatrix)
{
	if (pszSrcBuf == NULL || dwSrcBufLen == 0)
	{
		return;
	}
	
	strHexMatrix.clear();
	const DWORD dwTempLen = 10;
	char szTmp[dwTempLen]={0};

	for (DWORD dwIndex = 0; dwIndex < dwSrcBufLen; ++dwIndex) 
	{
		RtlZeroMemory(szTmp,dwTempLen);
		sprintf_s(szTmp,dwTempLen,"0x%02x ", static_cast<unsigned char>(((char*)pszSrcBuf)[dwIndex]));
		strHexMatrix.append(szTmp);
		if (dwIndex > 0 && dwIndex % 16 == 15)
		{
			strHexMatrix.append("\r\n");
		}
	}
	
}
