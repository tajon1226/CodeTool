// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Common/Logger.h" 
#include <iostream>
#include "inifiles.h"

using namespace INIFILE;
using namespace LOGGER; 
CLogger g_log(LogLevel_Info, CLogger::GetAppPathA().append("log\\")); 



//获取源代码文件名，不用输入参数




DWORD WINAPI Fun(LPVOID lpParamter)
{
	while(1) 
	{ 
		g_log.Fatal("Fun thread display[%s:%d]", CLogger::ExtractFileName(__FILE__).c_str(), __LINE__) ;
		Sleep(5000);
	}
}

void TestIni(void)
{

	TIniFile *iniSet = new TIniFile("..\\Debug\\set.ini");
	iniSet->WriteFloat("CodeTool", "float", 13.56);
	std::cout << iniSet->ReadFloat("CodeTool", "float", 44.55) << std::endl;


	iniSet->WriteBool("CodeTool", "bool", true);
	std::cout << iniSet->ReadBool("CodeTool", "bool", false) << std::endl;

	iniSet->WriteInteger("CodeTool", "LogLevel", LOGGER::LogLevel_Warning);
	LOGGER::EnumLogLevel logLevel = (LOGGER::EnumLogLevel)iniSet->ReadInteger("CodeTool", "LogLevel", LOGGER::LogLevel_Info);
	std::cout << "log level:" << logLevel << std::endl;
	g_log.ChangeLogLevel(logLevel);

}



void main() 
{
	HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);
	CloseHandle(hThread);

	TestIni();
	
	while (1)
	{
		g_log.Fatal("TraceFatal [%s:%d]", CLogger::ExtractFileName(__FILE__).c_str(), __LINE__); 
		g_log.Error("TraceError %s", "sun"); 
		string msg("string messages");
		g_log.Warn("TraceWarning %s", msg.c_str()); 
		g_log.Info("TraceInfo"); 

		g_log.Fatal("TraceFatal %d", 2); 
		g_log.Error("TraceError %f", 441.343567f); 
		g_log.Warn("TraceWarning"); 
		g_log.Info("TraceInfo"); 
		Sleep(1000);
	}




	std::cout << "已完成" << std::endl;
	getchar();
} 


