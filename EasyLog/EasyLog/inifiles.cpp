#include "stdafx.h"
#include "inifiles.h"
#include <stdlib.h>
#include <sstream>




namespace INIFILE
{
	#define  MAX_TXTLEN		256	//最大行数

	TIniFile::TIniFile(const CString FileName)
	{
		m_FileName = FileName;
	}

	TIniFile::~TIniFile()
	{

	}

	//-------------------------------------------------------------------------------------------------------

	CString TIniFile::ReadString(const CString Section, const CString Ident, const CString Default)
	{
		CString strValue;
		::GetPrivateProfileString(Section, Ident, Default, strValue.GetBuffer(MAX_TXTLEN), MAX_TXTLEN, m_FileName);
		strValue.ReleaseBuffer();
		return strValue;
	}
	//-------------------------------------------------------------------------------------------------------

	void TIniFile::WriteString(const CString Section, const CString Ident, const CString Value)
	{
		::WritePrivateProfileString(Section, Ident, Value, m_FileName);
	}

	//-------------------------------------------------------------------------------------------------------

	int TIniFile::ReadInteger(const CString Section, const CString Ident, int Default)
	{
		return ::GetPrivateProfileInt(Section, Ident, Default, m_FileName);
	}
	//-------------------------------------------------------------------------------------------------------

	void TIniFile::WriteInteger(const CString Section, const CString Ident, int Value)
	{
		CString strValue;
		strValue.Format("%d", Value);
		::WritePrivateProfileString(Section, Ident, strValue, m_FileName);
	}

	//-------------------------------------------------------------------------------------------------------

	double TIniFile::ReadFloat(const CString Section, const CString Ident, double Default)
	{
		CString strDefault;
		strDefault.Format("%lf", Default);

		CString strValue;
		::GetPrivateProfileString(Section, Ident, strDefault, strValue.GetBuffer(MAX_TXTLEN), MAX_TXTLEN, m_FileName);
		strValue.ReleaseBuffer();

		std::stringstream stream;
		double val;
		stream << strValue;
		stream >> val;
		return val;
	}

	//-------------------------------------------------------------------------------------------------------

	void TIniFile::WriteFloat(const CString Section, const CString Ident, double Value)
	{
		CString strValue;
		strValue.Format("%lf", Value);
		::WritePrivateProfileString(Section, Ident, strValue, m_FileName);
	}

	//-------------------------------------------------------------------------------------------------------
	bool TIniFile::ReadBool(const CString Section, const CString Ident, bool Default)
	{
		CString strDefault, strValue;
		strDefault.Format("%d", Default);
		::GetPrivateProfileString(Section, Ident, strDefault, strValue.GetBuffer(MAX_TXTLEN), MAX_TXTLEN, m_FileName);
		strValue.ReleaseBuffer();

		std::stringstream stream;
		bool val;
		stream << strValue;
		stream >> val;
		return val;
	}

	void TIniFile::WriteBool(const CString Section, const CString Ident, bool Value)
	{
		CString strValue;
		strValue.Format("%d", Value);
		::WritePrivateProfileString(Section, Ident, strValue, m_FileName);
	}

}// end namespace IniFile


