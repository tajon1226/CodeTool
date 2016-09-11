//logger.h  
/* 
//类名：CLogger 
//功能介绍：Win平台日志记录功能，多线程安全，支持写日志级别的设置，日志格式包含日志等级，日志时间，文件名，行号信息 
//作者：sunflover 2016-1-15 14:31:27 
 
//使用方法： 
1：将logger.h，logger.cpp添加到项目中 
2：设置logger.cpp的预编译头选项为“不使用预编译头” 
3：使用代码示例： 
#include "Logger.h" 
using namespace LOGGER; 
CLogger logger(LogLevel_Info,CLogger::GetAppPathA().append("log\\")); 
 
void main() 
{ 
logger.Fatal("TraceFatal %d", 1); 
logger.Error("TraceError %s", "sun"); 
logger.Warn("TraceWarning"); 
logger.Info("TraceInfo"); 
 
logger.ChangeLogLevel(LOGGER::LogLevel_Error); 
 
logger.Fatal("TraceFatal %d", 2); 
logger.Error("TraceError %s", "sun2"); 
logger.Warn("TraceWarning"); 
logger.Info("TraceInfo"); 
} 
 
 
执行结果：20160126_101329.log文件内容如下 
16-09-10 16:10:47 FATAL <> - TraceFatal 1
16-09-10 16:10:47 ERROR <> - TraceError sun
16-09-10 16:10:47 WARN <> - TraceWarning
16-09-10 16:10:47 INFO <> - TraceInfo
16-09-10 16:10:47 FATAL <> - TraceFatal 2
16-09-10 16:10:47 ERROR <> - TraceError sun2
*/  
  
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
        LogLevel_Fatal,     //只记录严重错误  
        LogLevel_Error,     //记录严重错误，普通错误  
        LogLevel_Warning,   //记录严重错误，普通错误，警告  
        LogLevel_Info       //记录严重错误，普通错误，警告，提示信息(也就是全部记录)  
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