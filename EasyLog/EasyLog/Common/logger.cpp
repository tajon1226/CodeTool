//logger.cpp  
#include "stdafx.h"
#include "logger.h"
#include "logger.h"  
#include <time.h>  
#include <stdarg.h>  
#include <direct.h>  
#include <vector>
#include <sstream>
#include <Dbghelp.h>  

#pragma comment(lib,"Dbghelp.lib") 

 
using std::vector;

namespace LOGGER  
{  
	CLogger::CLogger(EnumLogLevel nLogLevel, const string strLogPath, const string strLogName)  
		:m_nLogLevel(nLogLevel),  
		m_strLogPath(strLogPath),  
		m_strLogName(strLogName)  
	{  
 
		if (m_strLogPath.empty())  
		{  
			m_strLogPath = GetAppPathA();  
		}  
		if (m_strLogPath[m_strLogPath.length()-1] != '\\')  
		{  
			m_strLogPath.append("\\");  
		}  
		//创建文件夹  
		MakeSureDirectoryPathExists(m_strLogPath.c_str());  
		//创建日志文件  
		if (m_strLogName.empty())  
		{  
			time_t curTime;  
			time(&curTime);  
			tm tm1;  
			localtime_s(&tm1, &curTime);  
			m_strLogName = FormatString("%04d%02d%02d.log", tm1.tm_year + 1900, tm1.tm_mon + 1, tm1.tm_mday);   //日志的名称如：20160910.log
		}  
		m_strLogFilePath = m_strLogPath.append(m_strLogName);  

		//以追加的方式打开文件流  
		m_fout.open(m_strLogFilePath.c_str(), fstream::app, _SH_DENYNO);

		InitializeCriticalSection(&m_cs);  
	}  

	//-------------------------------------------------------------------------------------------------------------------------

	//析构函数  
	CLogger::~CLogger()  
	{  
		//释放临界区  
		DeleteCriticalSection(&m_cs);  
		//关闭文件流  
		if (m_fout)  
		{  
			m_fout.close();  
		}  
	}  


	//-------------------------------------------------------------------------------------------------------------------------

	//写严重错误信息  
	void CLogger::Fatal(const char *lpcszFormat, ...)  
	{  
		//判断当前的写日志级别  
		if (LogLevel_Fatal > m_nLogLevel)  
			return;  
		string strResult;  
		if (NULL != lpcszFormat)  
		{  
			va_list marker = NULL;  
			va_start(marker, lpcszFormat); //初始化变量参数  
			size_t nLength = _vscprintf(lpcszFormat, marker) + 1; //获取格式化字符串长度  
			std::vector<char> vBuffer(nLength, '\0'); //创建用于存储格式化字符串的字符数组  
			int nWritten = _vsnprintf_s(&vBuffer[0], vBuffer.size(), nLength, lpcszFormat, marker);  
			if (nWritten > 0)  
			{  
				strResult = &vBuffer[0];  
			}  
			va_end(marker); //重置变量参数  
		}  
		if (strResult.empty())  
		{  
			return;  
		}  
		string strLog = GetTime();  //IntToStr(GetCurrentThreadId()) + " " + 
		strLog.append(strFatalPrefix).append(strResult);  

		//写日志文件  
		Trace(strLog);  
	}  

	//-------------------------------------------------------------------------------------------------------------------------

	//写错误信息  
	void CLogger::Error(const char *lpcszFormat, ...)  
	{  
		//判断当前的写日志级别  
		if (LogLevel_Error > m_nLogLevel)  
			return;  
		string strResult;  
		if (NULL != lpcszFormat)  
		{  
			va_list marker = NULL;  
			va_start(marker, lpcszFormat); //初始化变量参数  
			size_t nLength = _vscprintf(lpcszFormat, marker) + 1; //获取格式化字符串长度  
			vector<char> vBuffer(nLength, '\0'); //创建用于存储格式化字符串的字符数组  
			int nWritten = _vsnprintf_s(&vBuffer[0], vBuffer.size(), nLength, lpcszFormat, marker);  
			if (nWritten > 0)  
			{  
				strResult = &vBuffer[0];  
			}  
			va_end(marker); //重置变量参数  
		}  
		if (strResult.empty())  
		{  
			return;  
		}  
		string strLog = GetTime();  
		strLog.append(strErrorPrefix).append(strResult);  

		//写日志文件  
		Trace(strLog);  
	}  

	//-------------------------------------------------------------------------------------------------------------------------

	//写警告信息  
	void CLogger::Warn(const char *lpcszFormat, ...)  
	{  
		//判断当前的写日志级别  
		if (LogLevel_Warning > m_nLogLevel)  
			return;  
		string strResult;  
		if (NULL != lpcszFormat)  
		{  
			va_list marker = NULL;  
			va_start(marker, lpcszFormat); //初始化变量参数  
			size_t nLength = _vscprintf(lpcszFormat, marker) + 1; //获取格式化字符串长度  
			vector<char> vBuffer(nLength, '\0'); //创建用于存储格式化字符串的字符数组  
			int nWritten = _vsnprintf_s(&vBuffer[0], vBuffer.size(), nLength, lpcszFormat, marker);  
			if (nWritten > 0)  
			{  
				strResult = &vBuffer[0];  
			}  
			va_end(marker); //重置变量参数  
		}  
		if (strResult.empty())  
		{  
			return;  
		}  
		string strLog = GetTime();  
		strLog.append(strWarningPrefix).append(strResult);  

		//写日志文件  
		Trace(strLog);  
	}  

	//-------------------------------------------------------------------------------------------------------------------------

	//写一般信息  
	void CLogger::Info(const char *lpcszFormat, ...)  
	{  
		//判断当前的写日志级别  
		if (LogLevel_Info > m_nLogLevel)  
			return;  
		string strResult;  
		if (NULL != lpcszFormat)  
		{  
			va_list marker = NULL;  
			va_start(marker, lpcszFormat); //初始化变量参数  
			size_t nLength = _vscprintf(lpcszFormat, marker) + 1; //获取格式化字符串长度  
			vector<char> vBuffer(nLength, '\0'); //创建用于存储格式化字符串的字符数组  
			int nWritten = _vsnprintf_s(&vBuffer[0], vBuffer.size(), nLength, lpcszFormat, marker);  
			if (nWritten > 0)  
			{  
				strResult = &vBuffer[0];  
			}  
			va_end(marker); //重置变量参数  
		}  
		if (strResult.empty())  
		{  
			return;  
		}  
		string strLog = GetTime();  
		strLog.append(strInfoPrefix).append(strResult);  

		//写日志文件  
		Trace(strLog);  
	}  

	//-------------------------------------------------------------------------------------------------------------------------

	//获取系统当前时间  
	string CLogger::GetTime()  
	{  
		time_t curTime;  
		time(&curTime);  
		tm tm1;  
		localtime_s(&tm1, &curTime);  
		//2016-01-01 21:30:00  
		string strTime = FormatString("%02d-%02d-%02d %02d:%02d:%02d ", (tm1.tm_year + 1900)%100, tm1.tm_mon + 1, tm1.tm_mday, tm1.tm_hour, tm1.tm_min, tm1.tm_sec);  

		return strTime;  
	}  

	//-------------------------------------------------------------------------------------------------------------------------

	//改变写日志级别  
	void CLogger::ChangeLogLevel(EnumLogLevel nLevel)  
	{  
		m_nLogLevel = nLevel;  
	}  

	//-------------------------------------------------------------------------------------------------------------------------

	//写文件操作  
	void CLogger::Trace(const string &strLog)  
	{  
		try  
		{  
			//进入临界区  
			EnterCriticalSection(&m_cs);  
			//若文件流没有打开，则重新打开  
			if (!m_fout.is_open())  
			{  
				m_fout.open(m_strLogFilePath.c_str(), fstream::app, _SH_DENYNO);  
				if (!m_fout)  
				{  
					return;  
				}  
			}  
			//写日志信息到文件流  
			m_fout << strLog.c_str() << std::endl;  
			//离开临界区  
			LeaveCriticalSection(&m_cs);  
		}  
		//若发生异常，则先离开临界区，防止死锁  
		catch (...)  
		{  
			LeaveCriticalSection(&m_cs);  
		}  
	}  

	//-------------------------------------------------------------------------------------------------------------------------

	string CLogger::GetAppPathA()  
	{  
		char szFilePath[MAX_PATH] = { 0 }, szDrive[MAX_PATH] = { 0 }, szDir[MAX_PATH] = { 0 }, szFileName[MAX_PATH] = { 0 }, szExt[MAX_PATH] = { 0 };  
		GetModuleFileNameA(NULL, szFilePath, sizeof(szFilePath));  
		_splitpath_s(szFilePath, szDrive, szDir, szFileName, szExt);  

		string str(szDrive);  
		str.append(szDir);  
		return str;  
	}  

	//-------------------------------------------------------------------------------------------------------------------------

	string CLogger::FormatString(const char *lpcszFormat, ...)  
	{  
		string strResult;  
		if (NULL != lpcszFormat)  
		{  
			va_list marker = NULL;  
			va_start(marker, lpcszFormat); //初始化变量参数  
			size_t nLength = _vscprintf(lpcszFormat, marker) + 1; //获取格式化字符串长度  
			vector<char> vBuffer(nLength, '\0'); //创建用于存储格式化字符串的字符数组  
			int nWritten = _vsnprintf_s(&vBuffer[0], vBuffer.size(), nLength, lpcszFormat, marker);  
			if (nWritten > 0)  
			{  
				strResult = &vBuffer[0];  
			}  
			va_end(marker); //重置变量参数  
		}  
		return strResult;  
	} 

	//-------------------------------------------------------------------------------------------------------------------------
	string CLogger::IntToStr(int val)
	{
		string tmp;
		std::stringstream ss;
		ss << val;
		ss >> tmp;
		return tmp;
	}


	//-------------------------------------------------------------------------------------------------------------------------
	//返回完整文件名中的文件名称 (带扩展名)，如"mytest.doc"
	string CLogger::ExtractFileName(const char *szFilePath)
	{
		char szDrive[MAX_PATH] = { 0 }, szDir[MAX_PATH] = { 0 }, szFileName[MAX_PATH] = { 0 }, szExt[MAX_PATH] = { 0 }; 
		_splitpath_s(szFilePath, szDrive, szDir, szFileName, szExt);
		string fileName = string(szFileName) + szExt;
		return fileName;
	}
	
}//end of namespace  LOGGER