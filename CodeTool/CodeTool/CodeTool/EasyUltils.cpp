#include "stdafx.h"
#include <Windows.h>
#include "EasyUltils.h"
#include <vector>
#include <sstream>

using std::vector;


namespace EASY_UlTILS
{
	string GetAppPathA()  
	{  
		char szFilePath[MAX_PATH] = { 0 }, szDrive[MAX_PATH] = { 0 }, szDir[MAX_PATH] = { 0 }, szFileName[MAX_PATH] = { 0 }, szExt[MAX_PATH] = { 0 };  
		GetModuleFileNameA(NULL, szFilePath, sizeof(szFilePath));  
		_splitpath_s(szFilePath, szDrive, szDir, szFileName, szExt);  

		string str(szDrive);  
		str.append(szDir);  
		return str;  
	}  

	//-------------------------------------------------------------------------------------------------------------------------

	string FormatString(const char *lpcszFormat, ...)  
	{  
		string strResult;  
		if (NULL != lpcszFormat)  
		{  
			va_list marker = NULL;  
			va_start(marker, lpcszFormat); //��ʼ����������  
			size_t nLength = _vscprintf(lpcszFormat, marker) + 1; //��ȡ��ʽ���ַ�������  
			vector<char> vBuffer(nLength, '\0'); //�������ڴ洢��ʽ���ַ������ַ�����  
			int nWritten = _vsnprintf_s(&vBuffer[0], vBuffer.size(), nLength, lpcszFormat, marker);  
			if (nWritten > 0)  
			{  
				strResult = &vBuffer[0];  
			}  
			va_end(marker); //���ñ�������  
		}  
		return strResult;  
	} 

	//-------------------------------------------------------------------------------------------------------------------------
	string IntToStr(int val)
	{
		string tmp;
		std::stringstream ss;
		ss << val;
		ss >> tmp;
		return tmp;
	}

	int StrToInt(const string str)
	{
		int iVal;
		std::stringstream stream(str);
		stream >> iVal;
		return iVal;
	}


	//-------------------------------------------------------------------------------------------------------------------------
	//���������ļ����е��ļ����� (����չ��)����"mytest.doc"
	string ExtractFileName(const char *szFilePath)
	{
		char szDrive[MAX_PATH] = { 0 }, szDir[MAX_PATH] = { 0 }, szFileName[MAX_PATH] = { 0 }, szExt[MAX_PATH] = { 0 }; 
		_splitpath_s(szFilePath, szDrive, szDir, szFileName, szExt);
		string fileName = string(szFileName) + szExt;
		return fileName;
	}

} //end namespace EASY_UlTILS


