#ifndef EasyUltilsSH  
#define EasyUltilsSH
#include <string>


using std::string;


namespace EASY_UlTILS
{
	string GetAppPathA();  //��ȡ��������·��,�������һ��\
	string ExtractFileName(const char *szFilePath);  //���������ļ����е��ļ����� (����չ��)����"mytest.doc"

	string FormatString(const char *lpcszFormat, ...);  //��ʽ���ַ���  
	string IntToStr(int val); 
	int StrToInt(const string str);
}



#endif