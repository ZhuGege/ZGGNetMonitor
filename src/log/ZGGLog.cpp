/**************************************************************************

Copyright:ZhuGege

Author: ZhuGege

Date:2016-03-13

Description:Inject DLL to Target Process

**************************************************************************/

#include "ZGGLog.h"
#include <time.h>
#include <tchar.h>

HANDLE CZGGLog::CLock::m_hEvent = CreateEvent(NULL,TRUE,TRUE,ZGGLOG_LOCK_EVENT_NAME);

//获取当前时间
std::string CZGGLog::GetLogTime()
{
	time_t stLogTime;
	char szLogTime[21] = {0};

	time(&stLogTime);
#pragma warning(disable:4996)
	strftime(szLogTime, 20, "%Y-%m-%d %H:%M:%S", localtime(&stLogTime));

	return string(szLogTime);
}

//创建日志
bool CZGGLog::InitLog(string strLogFileName)
{
	m_pFile = NULL;
	//成功返回0
	if(fopen_s(&m_pFile,strLogFileName.c_str(),"w+"))
		return false;
	
	return true;
}

bool CZGGLog::WriteInternal(string strLog)
{
	fwrite(strLog.c_str(),strLog.length(),1,m_pFile);

	return true;
}


