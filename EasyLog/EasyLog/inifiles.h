#pragma once

#include <atlstr.h>


namespace INIFILE
{
	class TIniFile
	{
	public:
		TIniFile(const CString FileName);
		virtual ~TIniFile();

	public:
		virtual CString ReadString(const CString Section, const CString Ident, const CString Default);
		virtual void WriteString(const CString Section, const CString Ident, const CString Value);
		virtual int ReadInteger(const CString Section, const CString Ident, int Default);
		virtual void WriteInteger(const CString Section, const CString Ident, int Value);
		virtual double ReadFloat(const CString Section, const CString Ident, double Default);		
		virtual void WriteFloat(const CString Section, const CString Ident, double Value);
		virtual bool ReadBool(const CString Section, const CString Ident, bool Default);
		virtual void WriteBool(const CString Section, const CString Ident, bool Value);

	private:
		CString m_FileName;
	};
}//end IniFile

