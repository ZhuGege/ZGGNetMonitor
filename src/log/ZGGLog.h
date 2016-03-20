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
//����ģʽ+����ģʽ+����ģʽ
class CZGGLog
{
public:
	enum LOG_OUTPUT_TYPE
	{
		LOG_OUTPUT_TYPE_LOG_TO_FILE			= 0x00000001, //д���ļ�
		LOG_OUTPUT_TYPE_LOG_TO_CONSOLE		= 0x00000010, //���������̨
		LOG_OUTPUT_TYPE_LOG_TO_REMOTE		= 0x00000100, //���͵�Զ�̶�
	};
	
	static CZGGLog* GetZGGLogInstance();
	BOOL InitLog(__in DWORD dwLogType,
				 __in const TCHAR* ptszLogFileName = _T("ZggLog.log")/*Ĭ������*/,
				 __in DWORD dwMaxOutputBufLen = 1024*1024 /*Ĭ�����1M�Ļ�����*/);
private:
	CZGGLog(){}
	CZGGLog(const CZGGLog&);
	CZGGLog& operator+(CZGGLog&);

	static CZGGLog* m_pObjZggLog;
	//ָ��������־
	static CLog* m_pObjLog;
};

}