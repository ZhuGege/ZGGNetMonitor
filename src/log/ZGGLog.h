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
//����ģʽ+����ģʽ+����ģʽ
class CZGGLog
{
public:
	typedef basic_string<TCHAR, char_traits<TCHAR>,
		allocator<TCHAR> > tstring;

	enum LOG_OUTPUT_TYPE
	{
		LOG_OUTPUT_TYPE_LOG_TO_FILE			= 0x00000001, //д���ļ�
		LOG_OUTPUT_TYPE_LOG_TO_CONSOLE		= 0x00000010, //���������̨
		LOG_OUTPUT_TYPE_LOG_TO_REMOTE		= 0x00000100, //���͵�Զ�̶�
	};
	
	static CZGGLog* GetZGGLogInstance();
	BOOL InitLog(__in DWORD dwLogType,
				 __in const TCHAR* ptszLogFileName = _T("ZggLog.log")/*Ĭ������*/);

	BOOL WriteLog(__in const TCHAR* fmt,...);
private:
	CZGGLog()
	{
		//���뻺��ռ�
		m_pszOutputBuf = new(std::nothrow) TCHAR[m_dwMaxOutputBufLen];
	}
	CZGGLog(const CZGGLog&);
	CZGGLog& operator+(CZGGLog&);

	//Ĭ�ϻ�������СΪ1MB
	const static DWORD  m_dwMaxOutputBufLen = 1024*1024;
	TCHAR* m_pszOutputBuf;

	static CZGGLog* m_pObjZggLog;
	//ָ��������־,֧��ͬʱ���������ն�
	static std::vector<ZGG::CLog*> m_vecObjLog;//
};

}