//logger.h  

//类名：CLogger 
//功能介绍：Win平台日志记录功能，多线程安全，支持写日志级别的设置，日志格式包含日志等级，日志时间，文件名，行号信息 
//作者：sunflover 2016-1-15 14:31:27 
//修正者:andy 2016-9-11 17:07 

  
#ifndef _LOGGER_H_  
#define _LOGGER_H_  
#include <Windows.h>  
#include <stdio.h>  
#include <string>  
#include <fstream>



using std::string; 
using std::fstream;
  
namespace LOGGER  
{  
    //日志级别的提示信息  
    static const string strFatalPrefix = "FATAL <> - ";  
    static const string strErrorPrefix = "ERROR <> - ";  
    static const string strWarningPrefix = "WARN <> - ";  
    static const string strInfoPrefix = "INFO <> - ";  
  
    //日志级别枚举  
    typedef enum EnumLogLevel  
    {  
        LogLevel_Stop = 0,  //什么都不记录  
        LogLevel_Fatal =1,     //只记录严重错误  
        LogLevel_Error = 2,     //记录严重错误，普通错误  
        LogLevel_Warning = 3,   //记录严重错误，普通错误，警告  
        LogLevel_Info = 4,       //记录严重错误，普通错误，警告，提示信息(也就是全部记录)  
    };  
  
    class CLogger  
    {  
    public:  
        //nLogLevel：日志记录的等级，可空  
        //strLogPath：日志目录，可空  
        //strLogName：日志名称，可空  
        CLogger(EnumLogLevel nLogLevel = LogLevel_Info, const string strLogPath = "", const string strLogName = "");  
        //析构函数  
        virtual ~CLogger();  

    public:  
        //写严重错误信息  
        void Fatal(const char *lpcszFormat, ...);  
        //写错误信息  
        void Error(const char *lpcszFormat, ...);  
        //写警告信息  
        void Warn(const char *lpcszFormat, ...);  
        //写提示信息  
        void Info(const char *lpcszFormat, ...);  
        //改变写日志级别  
        void ChangeLogLevel(EnumLogLevel nLevel);  
        //获取程序运行路径  
        static string GetAppPathA();  
        //格式化字符串  
        static string FormatString(const char *lpcszFormat, ...); 
		static string IntToStr(int val);
		//返回完整文件名中的文件名称 (带扩展名)，如"mytest.doc"
		static string ExtractFileName(const char *szFilePath); 

    private:  
        //写文件操作  
        void Trace(const string &strLog);  
        //获取当前系统时间  
        std::string GetTime();  


    private:  
        //写日志文件流  
		fstream m_fout; 
        //写日志级别  
        EnumLogLevel m_nLogLevel;  
        //日志目录  
        string m_strLogPath;  
        //日志的名称  
        string m_strLogName;  
        //日志文件全路径  
        string m_strLogFilePath;  
        //线程同步的临界区变量  
        CRITICAL_SECTION m_cs;  
    };  
}  
  
#endif  