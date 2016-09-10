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
//	printf("ÒÑÍê³É");
//
//
//
//
//	getchar();
//	return 0;
//}


#include "Common/Logger.h" 

using namespace LOGGER; 
CLogger logger(LogLevel_Info, CLogger::GetAppPathA().append("log\\")); 





void main() 
{
	for (int i=0; i<1; ++i)
	{
		logger.Fatal("TraceFatal %d", 1); 
		logger.Error("TraceError %s", "sun"); 
		logger.Warn("TraceWarning"); 
		logger.Info("TraceInfo"); 

		logger.ChangeLogLevel(LOGGER::LogLevel_Stop); 

		logger.Fatal("TraceFatal %d", 2); 
		logger.Error("TraceError %s", "sun2"); 
		logger.Warn("TraceWarning"); 
		logger.Info("TraceInfo"); 

	}

	
	getchar();
} 
