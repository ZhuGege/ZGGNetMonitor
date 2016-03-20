#include "ZGGLog.h"

/**************************************************************************

Copyright:ZhuGege

Author: ZhuGege

Date:2016-03-13

Description:log factory

**************************************************************************/

std::vector<ZGG::CLog*> ZGG::CZGGLog::m_vecObjLog;
ZGG::CZGGLog*		    ZGG::CZGGLog::m_pObjZggLog = NULL;


//***************************************************************
// Method:      GetZGGLogInstance
// FullName:    ZGG::CZGGLog::GetZGGLogInstance
// Access:      public static 
// Returns:     ZGG::CZGGLog*
// Qualifier:  
// Description: ��ȡһ����־����
//***************************************************************
ZGG::CZGGLog* ZGG::CZGGLog::GetZGGLogInstance()
{
	if (m_pObjZggLog == NULL)
	{	
		m_pObjZggLog = new CZGGLog;
	}
	return m_pObjZggLog;
}

//***************************************************************
// Method:      InitLog
// FullName:    ZGG::CZGGLog::InitLog
// Access:      public 
// Returns:     BOOL
// Qualifier:  
// Parameter:   __in DWORD dwLogType
// Parameter:   __in const TCHAR * ptszLogFileName
// Parameter:   __in DWORD dwMaxOutputBufLen
// Description: ��ʼ����־
//***************************************************************
BOOL ZGG::CZGGLog::InitLog(__in DWORD dwLogType,
						   __in const TCHAR* ptszLogFileName /*= _T("ZggLog.log")Ĭ������*/)
{
	switch(dwLogType)
	{
	case LOG_OUTPUT_TYPE_LOG_TO_FILE:
		{
			CLog* pObjLog = new(std::nothrow) CLogToFile(ptszLogFileName);

			if (pObjLog == NULL || !(pObjLog->InitLog()))
			{
				return FALSE;
			}
			//���뵽�ն�����б�
			m_vecObjLog.push_back(pObjLog);
			break;
		}
	default:
		{
			return FALSE;
		}
	}
	
	return TRUE;
}

//***************************************************************
// Method:      WriteLog
// FullName:    ZGG::CZGGLog::WriteLog
// Access:      public 
// Returns:     BOOL
// Qualifier:  
// Parameter:   __in const TCHAR * fmt
// Parameter:   ...
// Description: ���
//***************************************************************
BOOL ZGG::CZGGLog::WriteLog(__in const TCHAR* fmt,...)
{
	if (m_pszOutputBuf == NULL || fmt == NULL)
	{
		return FALSE;
	}
	
	//��ס
	CLog::CLock objLock;

	RtlZeroMemory(m_pszOutputBuf,m_dwMaxOutputBufLen * sizeof(TCHAR));
	va_list args; 
	va_start(args, fmt);				
	_vstprintf_s(m_pszOutputBuf, m_dwMaxOutputBufLen,fmt, args);
	va_end(args);


	tstring strWrite;
	TCHAR tszLogTime[21] = {0};
	CLog::GetLogTime(tszLogTime,_countof(tszLogTime));

	strWrite.assign(tszLogTime);
	strWrite.append(_T("  "));
	strWrite.append(m_pszOutputBuf);
	strWrite.append(_T("\r\n"));


	//��ע����ն�ȫ�����
	for (std::vector<CLog*>::iterator p = m_vecObjLog.begin(); p != m_vecObjLog.end(); p++)
	{
		if((*p) != NULL)
		{
			(*p)->WriteLog(strWrite.c_str(),strWrite.length()*sizeof(TCHAR));
		}
	}
	return TRUE;
}



