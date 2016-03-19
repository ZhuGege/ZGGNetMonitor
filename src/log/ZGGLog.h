#pragma once

/**************************************************************************

Copyright:ZhuGege

Author: ZhuGege

Date:2016-03-13

Description:Log Interface ,use strategy pattern

**************************************************************************/

namespace ZGG
{
//策略模式
class CZGGLog
{
public:
	enum LOG_OUTPUT_TYPE
	{
		LOG_OUTPUT_TYPE_LOG_TO_FILE			= 0x00000001, //写入文件
		LOG_OUTPUT_TYPE_LOG_TO_CONSOLE		= 0x00000010, //输出到控制台
		LOG_OUTPUT_TYPE_LOG_TO_REMOTE		= 0x00000100, //发送到远程端
	};

	BOOL InitLog(DWORD dwLogType);
	BOOL InitLog(DWORD dwLogType,TCHAR* ptszLogFileName);
};

}