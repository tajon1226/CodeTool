#include "stdafx.h"
#include "inifiles.h"

TIniFile::TIniFile(const CString FileName)
{
	m_FileName = FileName;
}


CString  TIniFile::ReadString(const CString Section, const CString Ident, const CString Default)
{
	CString valStr;
	::GetPrivateProfileString(Section, Ident, Default, valStr.GetBuffer(MAX_PATH), MAX_PATH, m_FileName);
	valStr.ReleaseBuffer();
	return valStr;
}

void TIniFile::WriteString(const CString Section, const CString Ident, const CString Value)
{
	::WritePrivateProfileString(Section, Ident, Value, m_FileName);
}

