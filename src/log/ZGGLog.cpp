#include "ZGGLog.h"

/**************************************************************************

Copyright:ZhuGege

Author: ZhuGege

Date:2016-03-13

Description:log factory

**************************************************************************/

ZGG::CLog*		ZGG::CZGGLog::m_pObjLog    = NULL;
ZGG::CZGGLog*   ZGG::CZGGLog::m_pObjZggLog = NULL;


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

BOOL ZGG::CZGGLog::InitLog(__in DWORD dwLogType,
						   __in const TCHAR* ptszLogFileName /*= _T("ZggLog.log")Ĭ������*/,
						   __in DWORD dwMaxOutputBufLen /*= 1024*1024 Ĭ�����1M�Ļ�����*/)
{
	switch(dwLogType)
	{
	case LOG_OUTPUT_TYPE_LOG_TO_FILE:
		{
			if (m_pObjLog != NULL)
			{
				delete m_pObjLog;
			}
			m_pObjLog = new CLogToFile(ptszLogFileName,dwMaxOutputBufLen);
		}
	}
	
	return TRUE;
}

