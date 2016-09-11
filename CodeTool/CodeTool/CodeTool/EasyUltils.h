#ifndef EasyUltilsSH  
#define EasyUltilsSH
#include <string>


using std::string;


namespace EASY_UlTILS
{
	string GetAppPathA();  //获取程序运行路径,包含最后一个\
	string ExtractFileName(const char *szFilePath);  //返回完整文件名中的文件名称 (带扩展名)，如"mytest.doc"

	string FormatString(const char *lpcszFormat, ...);  //格式化字符串  
	string IntToStr(int val); 
	int StrToInt(const string str);
}



#endif