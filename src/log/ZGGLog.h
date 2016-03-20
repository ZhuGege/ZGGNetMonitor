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
#include "vector"
#include "string"

namespace ZGG
{
//策略模式+单例模式+工厂模式
class CZGGLog
{
public:
	typedef basic_string<TCHAR, char_traits<TCHAR>,
		allocator<TCHAR> > tstring;

	enum LOG_OUTPUT_TYPE
	{
		LOG_OUTPUT_TYPE_LOG_TO_FILE			= 0x00000001, //写入文件
		LOG_OUTPUT_TYPE_LOG_TO_CONSOLE		= 0x00000010, //输出到控制台
		LOG_OUTPUT_TYPE_LOG_TO_REMOTE		= 0x00000100, //发送到远程端
	};
	
	static CZGGLog* GetZGGLogInstance();
	BOOL InitLog(__in DWORD dwLogType,
				 __in const TCHAR* ptszLogFileName = _T("ZggLog.log")/*默认名称*/);

	BOOL WriteLog(__in const TCHAR* fmt,...);
private:
	CZGGLog()
	{
		//申请缓冲空间
		m_pszOutputBuf = new(std::nothrow) TCHAR[m_dwMaxOutputBufLen];
	}
	CZGGLog(const CZGGLog&);
	CZGGLog& operator+(CZGGLog&);

	//默认缓冲区大小为1MB
	const static DWORD  m_dwMaxOutputBufLen = 1024*1024;
	TCHAR* m_pszOutputBuf;

	static CZGGLog* m_pObjZggLog;
	//指向具体的日志,支持同时输出到多个终端
	static std::vector<ZGG::CLog*> m_vecObjLog;//
};

}