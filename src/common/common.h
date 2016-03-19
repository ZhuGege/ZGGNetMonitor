#pragma once
/**************************************************************************

Copyright:ZhuGege

Author: ZhuGege

Date:2016-03-13

Description:Inject DLL to Target Process

**************************************************************************/
#include <string>

#define in_tchar

#define in_bytes




enum ZGG_NET_MONITOR_ERROR_CODE
{
	ZGG_NET_MONITOR_ERROR_CODE_OPEN_TARGET_PROCESS_FAILED=10000,
	ZGG_NET_MONITOR_ERROR_CODE_ALLOC_BUF_FROM_REMOTE_PROCESS_FAILED,
	ZGG_NET_MONITOR_ERROR_CODE_WRITE_REMOTE_PROCESS_FAILED,
	ZGG_NET_MONITOR_ERROR_CODE_CREATE_REMOTE_THREAD_FAILED,
};