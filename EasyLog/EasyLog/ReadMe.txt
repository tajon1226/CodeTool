//*debug +add -sub ^optimize

2016-9-10 wtz
+ IntToStr
^ threadid
^ FILE change to fstream

2016-9-10 wtz
fstream hFile;
hFile.open("me.txt",ios::app, _SH_DENYNO); 
����ʽ���������������ֵ��
0x10 //_SH_DENYRW Denies read and write access to the file 
0x20 //_SH_DENYWR Denies write access to the file 
0x30 //_SH_DENYRD Denies read access to the file. 
0x40 //_SH_DENYNO Permits read and write access 


mode�������õķ�ʽ���£�
fstream::app ��׷�ӵķ�ʽ��
fstream::ate �ļ��򿪺�λ���ļ�β
fstream::binary �Զ����Ʒ�ʽ���ļ���Ĭ�������ı���ʽ��
fstream::in �ļ��Զ�(����)��ʽ��
fstreamfstream::out �ļ���д(���)��ʽ��
iosfstream::trunc ����ļ����ڣ�����ļ����


2016-9-10 wtz
change the format output

2016-9-10 wtz
First Version