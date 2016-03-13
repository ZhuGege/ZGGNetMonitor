
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
		//获取目标进程HANDLE
		hProcess = OpenProcess(PROCESS_VM_OPERATION|PROCESS_VM_WRITE,FALSE,dwTargetPID); 
		if(hProcess == NULL) 
		{ 
			//printf("获取进程句柄错误%d",GetLastError()); 
			dwErrorCode = ZGG_NET_MONITOR_ERROR_CODE_OPEN_TARGET_PROCESS_FAILED;
			break;
		} 

		//在目标进程中分配即将注入DLL的名字空间
		lpRemoteBuf = VirtualAllocEx(hProcess,NULL,dwDllNameLength,MEM_COMMIT,PAGE_READWRITE); 
		if (lpRemoteBuf == NULL)
		{
			dwErrorCode = ZGG_NET_MONITOR_ERROR_CODE_ALLOC_BUF_FROM_REMOTE_PROCESS_FAILED;
			break;
		}
		
		//将DLL名字写入目标进程
		DWORD dwWriteBytes; 
		if(!WriteProcessMemory(hProcess,lpRemoteBuf,ptszDLLName,dwDllNameLength,&dwWriteBytes) || dwWriteBytes != dwDllNameLength) 
		{ 
			//如果写入失败，或者写入的长度于传入的长度不一致，均做失败处理
			//printf("写入远程进程内存空间出错%d。",GetLastError());	
			dwErrorCode = ZGG_NET_MONITOR_ERROR_CODE_WRITE_REMOTE_PROCESS_FAILED;
			break;

		}

		//创建远程线程
		DWORD dwInjectThreadId; 
		LPVOID lpRemoteThreadAddr = LoadLibrary; 
		HANDLE hInjectThread = CreateRemoteThread(hProcess,NULL,0,(LPTHREAD_START_ROUTINE)lpRemoteThreadAddr,lpRemoteBuf,0,&dwInjectThreadId); 
		if(hInjectThread == NULL) 
		{ 
			//printf("建立远程线程失败%d",GetLastError()); 
			dwErrorCode = ZGG_NET_MONITOR_ERROR_CODE_CREATE_REMOTE_THREAD_FAILED;
			break;
		} 
		
		//等待DLL注入完成
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
