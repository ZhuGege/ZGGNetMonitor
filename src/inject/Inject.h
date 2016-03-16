#pragma once
/**************************************************************************

Copyright:ZhuGege

Author: ZhuGege

Date:2016-03-13

Description:Inject DLL to Target Process

**************************************************************************/
#include <windows.h>

class CInject
{

private:
	DWORD GetTargetProcessID(__in TCHAR* ptszProcessName, __out DWORD& dwPID);
	DWORD InjectDLLByCreateRemoteThread(__in DWORD dwTargetPID, __in TCHAR* ptszDLLName);
	BOOL  enableDebugPriv();
};