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
CLogger logger(LogLevel_Info,CLogger::GetAppPathA().append("log\\")); 

void main() 
{
	for (int i=0; i<1000; ++i)
	{
		logger.TraceFatal("TraceFatal %d", 1); 
		logger.TraceError("TraceError %s", "sun"); 
		logger.TraceWarning("TraceWarning"); 
		logger.TraceInfo("TraceInfo"); 

		logger.ChangeLogLevel(LOGGER::LogLevel_Error); 

		logger.TraceFatal("TraceFatal %d", 2); 
		logger.TraceError("TraceError %s", "sun2"); 
		logger.TraceWarning("TraceWarning"); 
		logger.TraceInfo("TraceInfo"); 

	}


	getchar();
} 