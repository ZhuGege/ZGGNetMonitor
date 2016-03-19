#include "gtest/gtest.h"
#include "Log.h"
#include "LogToFile.h"

#pragma warning(disable:4800)

TEST(GetLogTime,ZGGLog)
{
	ZGG::CLog * pobjLog = new ZGG::CLogToFile;
	TCHAR tszLogTime[44] = {0};
	EXPECT_TRUE(pobjLog->GetLogTime(tszLogTime,_countof(tszLogTime)));
	_tprintf(_T("%s\n"),tszLogTime);

	char szText[] = "test for log,11112222222222222222222233333333333333";
	std::string strHexMatrix;
	pobjLog->ConvertBufToHexMatrix(szText,_countof(szText),strHexMatrix);
	printf("%s\n",strHexMatrix.c_str());

	EXPECT_TRUE(pobjLog->InitLog(_T("test.log")));
	EXPECT_TRUE(pobjLog->WriteLog(_T("write by ÷Ï∏Á∏Á")));

}