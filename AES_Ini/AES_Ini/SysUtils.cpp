#include "stdafx.h"
#include "SysUtils.h"

CString ExtractFileDir(const CString FileName)
{
	CString fileDir = FileName.Mid(0, FileName.ReverseFind('\\'));
	return fileDir;
}

CString GetExeFileDir()
{
	CString exeName;
	GetModuleFileName(NULL, exeName.GetBuffer(MAX_PATH), MAX_PATH); 
	exeName.ReleaseBuffer();

	return ExtractFileDir(exeName);
}