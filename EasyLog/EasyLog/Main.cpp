// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#include "Common/Logfile.h"
//int _tmain(int argc, _TCHAR* argv[])
//{
//	LogFileEx log("../Debug/Logfiles");
//
//	for (int i=0; i<1000; ++i)
//		log.Log("4646456015555555555555555555555555555555555555");
//
//	printf("已完成");
//
//
//
//
//	getchar();
//	return 0;
//}


#include "Common/Logger.h" 
#include <iostream>




using namespace LOGGER; 
CLogger logger(LogLevel_Info, CLogger::GetAppPathA().append("log\\")); 



//获取源代码文件名，不用输入参数




DWORD WINAPI Fun(LPVOID lpParamter)
{
	while(1) 
	{ 
		logger.Fatal("Fun thread display[%s:%d]", CLogger::ExtractFileName(__FILE__).c_str(), __LINE__) ;
		Sleep(5000);
	}
}



void main() 
{
	HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);
	CloseHandle(hThread);


	while (1)
	{
		logger.Fatal("TraceFatal [%s:%d]", CLogger::ExtractFileName(__FILE__).c_str(), __LINE__); 
		logger.Error("TraceError %s", "sun"); 
		string msg("string messages");
		logger.Warn("TraceWarning %s", msg.c_str()); 
		logger.Info("TraceInfo"); 

		//logger.ChangeLogLevel(LOGGER::LogLevel_Stop); 

		logger.Fatal("TraceFatal %d", 2); 
		logger.Error("TraceError %f", 441.343567f); 
		logger.Warn("TraceWarning"); 
		logger.Info("TraceInfo"); 
		Sleep(1000);
	}




	printf("已完成");
	getchar();
} 


