
/**************************************************************************

Copyright:ZhuGege

Author: ZhuGege

Date:2016-03-13

Description:Inject DLL to Target Process

**************************************************************************/
#include "Inject.h"
#include "common.h"
#include <tchar.h>

DWORD CInject::InjectDLLByCreateRemoteThread(__in DWORD dwTargetPID, __in TCHAR* ptszDLLName)
{
	DWORD dwErrorCode = ERROR_SUCCESS;
	HANDLE hProcess = NULL;
	LPVOID lpRemoteBuf = NULL;
	DWORD dwDllNameLength = (_tcslen(ptszDLLName) + 1) * sizeof(TCHAR);  

	do 
	{
		//��ȡĿ�����HANDLE
		hProcess = OpenProcess(PROCESS_VM_OPERATION|PROCESS_VM_WRITE,FALSE,dwTargetPID); 
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
