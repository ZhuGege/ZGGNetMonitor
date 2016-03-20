#pragma once

/**************************************************************************

Copyright:ZhuGege

Author: ZhuGege

Date:2016-03-13

Description:Log Interface ,use strategy pattern

**************************************************************************/

#include <windows.h>
#include "Log.h"
#include "LogToFile.h"

namespace ZGG
{
//策略模式+单例模式+工厂模式
class CZGGLog
{
public:
	enum LOG_OUTPUT_TYPE
	{
		LOG_OUTPUT_TYPE_LOG_TO_FILE			= 0x00000001, //写入文件
		LOG_OUTPUT_TYPE_LOG_TO_CONSOLE		= 0x00000010, //输出到控制台
		LOG_OUTPUT_TYPE_LOG_TO_REMOTE		= 0x00000100, //发送到远程端
	};
	
	static CZGGLog* GetZGGLogInstance();
	BOOL InitLog(__in DWORD dwLogType,
				 __in const TCHAR* ptszLogFileName = _T("ZggLog.log")/*默认名称*/,
				 __in DWORD dwMaxOutputBufLen = 1024*1024 /*默认最大1M的缓冲区*/);
private:
	CZGGLog(){}
	CZGGLog(const CZGGLog&);
	CZGGLog& operator+(CZGGLog&);

	static CZGGLog* m_pObjZggLog;
	//指向具体的日志
	static CLog* m_pObjLog;
};

}