
/**************************************************************************

Copyright:ZhuGege

Author: ZhuGege

Date:2016-03-13

Description:Inject DLL to Target Process

**************************************************************************/
#include "Inject.h"
#include "common.h"
#include <tchar.h>


BOOL CInject::enableDebugPriv()
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;

	if (!OpenProcessToken(GetCurrentProcess(), 
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
			return false;
	}
	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue)) {
		CloseHandle(hToken);
		return false;
	}
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL)) {
		CloseHandle(hToken);
		return false;
	}
	return true;
}

DWORD CInject::InjectDLLByCreateRemoteThread(__in DWORD dwTargetPID, __in TCHAR* ptszDLLName)
{
	DWORD dwErrorCode = ERROR_SUCCESS;
	HANDLE hProcess = NULL;
	LPVOID lpRemoteBuf = NULL;
	DWORD dwDllNameLength = (_tcslen(ptszDLLName) + 1) * sizeof(TCHAR);  

	do 
	{
		//��ȡĿ�����HANDLE
		hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,dwTargetPID); 
		if(hProcess == NULL) 
		{ 
			//printf("��ȡ���̾������%d",GetLastError()); 
			dwErrorCode = ZGG_NET_MONITOR_ERROR_CODE_OPEN_TARGET_PROCESS_FAILED;
			break;
		} 

		//��Ŀ������з��伴��ע��DLL�����ֿռ�
		lpRemoteBuf = VirtualAllocEx(hProcess,NULL,dwDllNameLength,MEM_COMMIT,PAGE_READWRITE); 
		if (lpRemoteBuf == NULL)
		{
			dwErrorCode = ZGG_NET_MONITOR_ERROR_CODE_ALLOC_BUF_FROM_REMOTE_PROCESS_FAILED;
			break;
		}
		
		//��DLL����д��Ŀ�����
		DWORD dwWriteBytes; 
		if(!WriteProcessMemory(hProcess,lpRemoteBuf,ptszDLLName,dwDllNameLength,&dwWriteBytes) || dwWriteBytes != dwDllNameLength) 
		{ 
			//���д��ʧ�ܣ�����д��ĳ����ڴ���ĳ��Ȳ�һ�£�����ʧ�ܴ���
			//printf("д��Զ�̽����ڴ�ռ����%d��",GetLastError());	
			dwErrorCode = ZGG_NET_MONITOR_ERROR_CODE_WRITE_REMOTE_PROCESS_FAILED;
			break;

		}

		//����Զ���߳�
		DWORD dwInjectThreadId; 
		LPVOID lpRemoteThreadAddr = LoadLibrary; 
		HANDLE hInjectThread = CreateRemoteThread(hProcess,NULL,0,(LPTHREAD_START_ROUTINE)lpRemoteThreadAddr,lpRemoteBuf,0,&dwInjectThreadId); 
		if(hInjectThread == NULL) 
		{ 
			//printf("����Զ���߳�ʧ��%d",GetLastError()); 
			dwErrorCode = ZGG_NET_MONITOR_ERROR_CODE_CREATE_REMOTE_THREAD_FAILED;
			break;
		} 
		
		//�ȴ�DLLע�����
		WaitForSingleObject(hInjectThread,INFINITE); 
		CloseHandle(hInjectThread); 

	} while (FALSE);
	
	if (lpRemoteBuf != NULL)
	{
		VirtualFreeEx(hProcess,lpRemoteBuf,dwDllNameLength,MEM_COMMIT); 
	}
	if (hProcess != NULL)
	{
		CloseHandle(hProcess); 
	}
	return dwErrorCode;
}
