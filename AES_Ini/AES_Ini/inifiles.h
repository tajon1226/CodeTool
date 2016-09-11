#pragma once

class TIniFile
{
public:
	TIniFile(const CString FileName);
	virtual ~TIniFile(void) {}
	virtual CString  ReadString(const CString Section, const CString Ident, const CString Default);
	virtual void WriteString(const CString Section, const CString Ident, const CString Value);
	//virtual int  ReadInteger(const CString Section, const CString Ident, int Default) = 0; //暂时不实现 
	//virtual void WriteInteger(const CString Section, const CString Ident, int Value) = 0; //暂时不实现

private:
	CString m_FileName;
};
