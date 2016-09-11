//logger.h  

//������CLogger 
//���ܽ��ܣ�Winƽ̨��־��¼���ܣ����̰߳�ȫ��֧��д��־��������ã���־��ʽ������־�ȼ�����־ʱ�䣬�ļ������к���Ϣ 
//���ߣ�sunflover 2016-1-15 14:31:27 
//������:andy 2016-9-11 17:07 

  
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
    //��־�������ʾ��Ϣ  
    static const string strFatalPrefix = "FATAL <> - ";  
    static const string strErrorPrefix = "ERROR <> - ";  
    static const string strWarningPrefix = "WARN <> - ";  
    static const string strInfoPrefix = "INFO <> - ";  
  
    //��־����ö��  
    typedef enum EnumLogLevel  
    {  
        LogLevel_Stop = 0,  //ʲô������¼  
        LogLevel_Fatal =1,     //ֻ��¼���ش���  
        LogLevel_Error = 2,     //��¼���ش�����ͨ����  
        LogLevel_Warning = 3,   //��¼���ش�����ͨ���󣬾���  
        LogLevel_Info = 4,       //��¼���ش�����ͨ���󣬾��棬��ʾ��Ϣ(Ҳ����ȫ����¼)  
    };  
  
    class CLogger  
    {  
    public:  
        //nLogLevel����־��¼�ĵȼ����ɿ�  
        //strLogPath����־Ŀ¼���ɿ�  
        //strLogName����־���ƣ��ɿ�  
        CLogger(EnumLogLevel nLogLevel = LogLevel_Info, const string strLogPath = "", const string strLogName = "");  
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
        static string GetAppPathA();  
        //��ʽ���ַ���  
        static string FormatString(const char *lpcszFormat, ...); 
		static string IntToStr(int val);
		//���������ļ����е��ļ����� (����չ��)����"mytest.doc"
		static string ExtractFileName(const char *szFilePath); 

    private:  
        //д�ļ�����  
        void Trace(const string &strLog);  
        //��ȡ��ǰϵͳʱ��  
        std::string GetTime();  


    private:  
        //д��־�ļ���  
		fstream m_fout; 
        //д��־����  
        EnumLogLevel m_nLogLevel;  
        //��־Ŀ¼  
        string m_strLogPath;  
        //��־������  
        string m_strLogName;  
        //��־�ļ�ȫ·��  
        string m_strLogFilePath;  
        //�߳�ͬ�����ٽ�������  
        CRITICAL_SECTION m_cs;  
    };  
}  
  
#endif  