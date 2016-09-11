//*debug +add -sub ^optimize

2016-9-10 wtz
+ IntToStr
^ threadid
^ FILE change to fstream

2016-9-10 wtz
fstream hFile;
hFile.open("me.txt",ios::app, _SH_DENYNO); 
共享方式参数可以是下面的值：
0x10 //_SH_DENYRW Denies read and write access to the file 
0x20 //_SH_DENYWR Denies write access to the file 
0x30 //_SH_DENYRD Denies read access to the file. 
0x40 //_SH_DENYNO Permits read and write access 


mode可以设置的方式如下：
fstream::app 以追加的方式打开
fstream::ate 文件打开后定位到文件尾
fstream::binary 以二进制方式打开文件，默认是以文本方式打开
fstream::in 文件以读(输入)方式打开
fstreamfstream::out 文件以写(输出)方式打开
iosfstream::trunc 如果文件存在，则把文件清空


2016-9-10 wtz
change the format output

2016-9-10 wtz
First Version