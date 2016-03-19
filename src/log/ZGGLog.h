#pragma once

/**************************************************************************

Copyright:ZhuGege

Author: ZhuGege

Date:2016-03-13

Description:Log Interface ,use strategy pattern

**************************************************************************/

namespace ZGG
{
//����ģʽ
class CZGGLog
{
public:
	enum LOG_OUTPUT_TYPE
	{
		LOG_OUTPUT_TYPE_LOG_TO_FILE			= 0x00000001, //д���ļ�
		LOG_OUTPUT_TYPE_LOG_TO_CONSOLE		= 0x00000010, //���������̨
		LOG_OUTPUT_TYPE_LOG_TO_REMOTE		= 0x00000100, //���͵�Զ�̶�
	};

	BOOL InitLog(DWORD dwLogType);
	BOOL InitLog(DWORD dwLogType,TCHAR* ptszLogFileName);
};

}