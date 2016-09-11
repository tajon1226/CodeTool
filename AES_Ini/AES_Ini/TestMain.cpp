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

		char KEY[17] = "0123456789abcdef"; //������16�ֽ�
		int ret = EncFile(plainTextFile, encFile, KEY);

		if (ret == ENC_OK)
		{
			printf("���ܳɹ���\n");
		}
		else if (ret == ENC_FILE_ERR)
		{
			printf("EncFile�ڴ�������\n");
		}
		else if (ret == ENC_FILE_ERR)
		{
			printf("EncFile-�ļ��򿪴���\n");
		}

		ret = DecFile(encFile, decFile, KEY);
		if (ret == ENC_OK)
		{
			printf("���ܳɹ���\n");
		}
		else if (ret == ENC_FILE_ERR)
		{
			printf("EncFile�ڴ�������\n");
		}
		else if (ret == ENC_FILE_ERR)
		{
			printf("EncFile-�ļ��򿪴���\n");
		}

		TIniFile *ini = new TIniFile(decFile);
		printf("������ڼ�ֵ��%s\n", ini->ReadString("APP", "�������", "·"));
		
	}

	system("pause");
	return nRetCode;
}
