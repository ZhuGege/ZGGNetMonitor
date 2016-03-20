/**************************************************************************

Copyright:ZhuGege

Author: ZhuGege

Date:2016-03-13

Description:abstract log

**************************************************************************/

#include "Log.h"
#include <time.h>

HANDLE ZGG::CLog::CLock::m_hEvent = NULL;

//***************************************************************
// Method:      GetLogTime
// FullName:    CZGGLog::GetLogTime
// Access:      virtual public 
// Returns:     BOOL
// Qualifier:  
// Parameter:   TCHAR * ptszLogTimeBuf
// Parameter:   DWORD dwBufLen ,in tchar
// Description: ��ȡ��ǰʱ��
//***************************************************************
BOOL ZGG::CLog::GetLogTime(__out TCHAR* ptszLogTimeBuf, __in DWORD  dwBufLen/*in tchar*/)
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
// Description: ���ַ���ת��Ϊʮ�����ƾ���
//***************************************************************
void ZGG::CLog::ConvertBufToHexMatrix(__in const void* pszSrcBuf,
									  __in DWORD dwSrcBufLen/*in bytes*/,
									  __out std::string& strHexMatrix)
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
