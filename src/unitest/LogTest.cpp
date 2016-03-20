#include "gtest/gtest.h"
#include "Log.h"
#include "LogToFile.h"
#include "ZGGLog.h"

#pragma warning(disable:4800)

TEST(Log,CLogToFile)
{
	ZGG::CLog * pobjLog = new ZGG::CLogToFile(_T("test.log"));
	TCHAR tszLogTime[44] = {0};
	EXPECT_TRUE(pobjLog->GetLogTime(tszLogTime,_countof(tszLogTime)));
	_tprintf(_T("%s\n"),tszLogTime);

	char szText[] = "test for log,11112222222222222222222233333333333333";
	std::string strHexMatrix;
	pobjLog->ConvertBufToHexMatrix(szText,_countof(szText),strHexMatrix);
	printf("%s\n",strHexMatrix.c_str());

	EXPECT_TRUE(pobjLog->InitLog());
	TCHAR tszText[] = _T("write by zhugege\r\n");
	EXPECT_TRUE(pobjLog->WriteLog(tszText,(_countof(tszText) - 1)*sizeof(TCHAR)));

}

TEST(Log,CZGGLog)
{
	ZGG::CZGGLog* pObjZGGlog = ZGG::CZGGLog::GetZGGLogInstance();

	EXPECT_TRUE(pObjZGGlog->InitLog(ZGG::CZGGLog::LOG_OUTPUT_TYPE_LOG_TO_FILE,_T("zhugege.log")));
	EXPECT_TRUE(pObjZGGlog->WriteLog(_T("test for %s%d"),_T("zhugege"),122));
}