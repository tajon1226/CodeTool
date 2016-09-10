//�ɰ��������ɶ����־�� ���ɷ�������Ƶ�������ļ���

//����������ù�ҵ�ֳ�24X7ֵ�صĳ����¼������Ϣ�� ������;
//һ����һ��ȫ����־���� ���ٽ��ų���Զ��̰߳�ȫʹ�á�
//��������
//class LogFile;//�û�������־�ļ���
//class LogFileEx;//����־�ļ����Զ����ɹ��� , �ɷ�������Ƶ�������ļ���, ��ָ����־��ŵ�Ŀ¼
//LogFile gLog("My.Log");
//gLog.Log("test", 4);//��¼��־
//gLog.Log("ϵͳ����");
//LogFileEx gLog(".", LogFileEx :: YEAR);//һ������һ����־�ļ�
//LogFileEx gLog(".//Log", LogFileEx :: MONTH);//һ������һ����־�ļ�
//LogFileEx gLog(".//Log", LogFileEx :: DAY);//һ������һ����־�ļ�
//ע����־����Ŀ¼����ʧ�ܻ��Զ��˳��� ��ע��Ŀ¼�ĺϷ��ԣ� �ļ�����Ƶ�ʿ��������
//24Сʱ���еĳ������ÿ������һ����־�ļ��� �������ݹ���


#ifndef _LOGFILE_H
#define _LOGFILE_H
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>


class LogFile
{
public:

	LogFile(const char *szFileName = "Log.log"); //�趨��־�ļ���
	virtual ~LogFile();
	const char * GetFileName(){ return _szFileName; }
	void SetFileName(const char *szName); //�޸��ļ����� ͬʱ�ر���һ����־�ļ�
	bool IsOpen() { return _hFile != INVALID_HANDLE_VALUE; }
	void Close();
	void Log(LPCVOID lpBuffer, DWORD dwLength); //׷����־����
	void Log(const char *szText){ Log(szText, strlen(szText)); }

protected:
	CRITICAL_SECTION _csLock;
	char _szFileName[MAX_PATH + 1];
	HANDLE _hFile;

	bool OpenFile(); //���ļ��� ָ�뵽�ļ�β
	DWORD Write(LPCVOID lpBuffer, DWORD dwLength);
	virtual void WriteLog( LPCVOID lpBuffer, DWORD dwLength); //д��־, ������չ�޸�
	void Lock()  { ::EnterCriticalSection(&_csLock); }
	void Unlock() { ::LeaveCriticalSection(&_csLock); }


private://���κ���
	LogFile(const LogFile&);
	LogFile&operator = (const LogFile&);
};


class LogFileEx : public LogFile
{
public:
	enum LOG_TYPE{YEAR = 0, MONTH = 1, DAY = 2};
	LogFileEx(const char *szPath = ".", LOG_TYPE iType = MONTH);
	~LogFileEx();
	const char * GetPath(){ return _szPath; }
	void Log(LPCVOID lpBuffer, DWORD dwLength);
	void Log(const char *szText){ Log(szText, strlen(szText)); }

protected:
	char _szPath[MAX_PATH + 1];
	char _szLastDate[20];
	int _iType;
	void SetPath(const char *szPath);

private://���κ���
	LogFileEx(const LogFileEx&);
	LogFileEx&operator = (const LogFileEx&);
};
#endif