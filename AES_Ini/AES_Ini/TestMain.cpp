// AES_Ini.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TestMain.h"
#include "Algorithm/EncFile.h"
#include "SysUtils.h"
#include "inifiles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		
		CString FileDir = GetExeFileDir();
		CString plainTextFile = FileDir + "\\set.ini";
		CString encFile = FileDir + "\\set_enc.ini";
		CString decFile = FileDir + "\\set_restored.ini";

		char KEY[17] = "0123456789abcdef"; //必须是16字节
		int ret = EncFile(plainTextFile, encFile, KEY);

		if (ret == ENC_OK)
		{
			printf("解密成功！\n");
		}
		else if (ret == ENC_FILE_ERR)
		{
			printf("EncFile内存分配错误\n");
		}
		else if (ret == ENC_FILE_ERR)
		{
			printf("EncFile-文件打开错误\n");
		}

		ret = DecFile(encFile, decFile, KEY);
		if (ret == ENC_OK)
		{
			printf("解密成功！\n");
		}
		else if (ret == ENC_FILE_ERR)
		{
			printf("EncFile内存分配错误\n");
		}
		else if (ret == ENC_FILE_ERR)
		{
			printf("EncFile-文件打开错误\n");
		}

		TIniFile *ini = new TIniFile(decFile);
		printf("天道酬勤键值：%s\n", ini->ReadString("APP", "天道酬勤", "路"));
		
	}

	system("pause");
	return nRetCode;
}
