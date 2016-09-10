//logger.h  
/* 
//������CLogger 
//���ܽ��ܣ�Winƽ̨��־��¼���ܣ����̰߳�ȫ��֧��д��־��������ã���־��ʽ������־�ȼ�����־ʱ�䣬�ļ������к���Ϣ 
//���ߣ�sunflover 2016-1-15 14:31:27 
 
//ʹ�÷����� 
1����logger.h��logger.cpp��ӵ���Ŀ�� 
2������logger.cpp��Ԥ����ͷѡ��Ϊ����ʹ��Ԥ����ͷ�� 
3��ʹ�ô���ʾ���� 
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
 
 
ִ�н����20160126_101329.log�ļ��������� 
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
  
namespace LOGGER  
{  
    //��־�������ʾ��Ϣ  
    static const std::string strFatalPrefix = "FATAL <> - ";  
    static const std::string strErrorPrefix = "ERROR <> - ";  
    static const std::string strWarningPrefix = "WARN <> - ";  
    static const std::string strInfoPrefix = "INFO <> - ";  
  
    //��־����ö��  
    typedef enum EnumLogLevel  
    {  
        LogLevel_Stop = 0,  //ʲô������¼  
        LogLevel_Fatal,     //ֻ��¼���ش���  
        LogLevel_Error,     //��¼���ش�����ͨ����  
        LogLevel_Warning,   //��¼���ش�����ͨ���󣬾���  
        LogLevel_Info       //��¼���ش�����ͨ���󣬾��棬��ʾ��Ϣ(Ҳ����ȫ����¼)  
    };  
  
    class CLogger  
    {  
    public:  
        //nLogLevel����־��¼�ĵȼ����ɿ�  
        //strLogPath����־Ŀ¼���ɿ�  
        //strLogName����־���ƣ��ɿ�  
        CLogger(EnumLogLevel nLogLevel = EnumLogLevel::LogLevel_Info, const std::string strLogPath = "", const std::string strLogName = "");  
        //��������  
        virtual ~CLogger();  

    public:  
        //д���ش�����Ϣ  
        void Fatal(const char *lpcszFormat, ...);  
        //д������Ϣ  
        void Error(const char *lpcszFormat, ...);  
        //д������Ϣ  
        void Warn(const char *lpcszFormat, ...);  
        //д��ʾ��Ϣ  
        void Info(const char *lpcszFormat, ...);  
        //�ı�д��־����  
        void ChangeLogLevel(EnumLogLevel nLevel);  
        //��ȡ��������·��  
        static std::string GetAppPathA();  
        //��ʽ���ַ���  
        static std::string FormatString(const char *lpcszFormat, ...); 

    private:  
        //д�ļ�����  
        void Trace(const std::string &strLog);  
        //��ȡ��ǰϵͳʱ��  
        std::string GetTime();  
        //�ļ�ȫ·���õ��ļ���  
        const char *path_file(const char *path, char splitter);


    private:  
        //д��־�ļ���  
        FILE * m_pFileStream;  
        //д��־����  
        EnumLogLevel m_nLogLevel;  
        //��־Ŀ¼  
        std::string m_strLogPath;  
        //��־������  
        std::string m_strLogName;  
        //��־�ļ�ȫ·��  
        std::string m_strLogFilePath;  
        //�߳�ͬ�����ٽ�������  
        CRITICAL_SECTION m_cs;  
    };  
}  
  
#endif  