#include "stdafx.h"
#include "EncFile.h"
#include <fstream>
#include <string.h>
#include "AesCipher.h"
#include "Base64.h"

using namespace std;


static char g_inBuf[102400000] = {0};



//--------------------------------------------------------------------
//������ �� EncFile
//������������ �������ļ���ͨ��AES + base64���ܣ�
//�������� ��inFile�����ļ���, outFile�����ļ��� KEY-16�ֽ���Կ 
//��������ֵ �� 0�ɹ� 1�ļ��򿪴� 2�ڴ�������
//���� �������
//������������ �� 2016-8-23
//�����޸����� ��  2016-8-26
//�޸��� �������
//�޸�ԭ�� �� 
//�汾 �� 1.02
//��ʷ�汾 �� 1.01
//--------------------------------------------------------------------
int EncFile(const char *inFile, const char *outFile, const char *KEY)
{
	ifstream fin(inFile);
	if (!fin) return ENC_FILE_ERR;


	fin.seekg(0, ios::end);   
	int fileSize  = fin.tellg();  
	fin.seekg(0, ios::beg);
	fin.read(g_inBuf, fileSize);
	fin.close();


	AesCipher crypto;
	char counter[16] = {0};
	counter[5] = -113;
	crypto.makeRoundKey(KEY, 16);  
	crypto.setCounter(counter);

	//AES����
	int tempLen = strlen(g_inBuf);
	int outLen = crypto.calculateCipherLen(tempLen);
	char *outBuf = new char[outLen];
	if (outBuf == NULL) return ENC_MEMORY_ERR;
	ZeroMemory(outBuf, outLen);
	crypto.encryptString(g_inBuf, outBuf, strlen(g_inBuf), AesCipher::CTR);

	//BASE64����
	int base64Len = Base64::calculateBase64Len(outLen); //base64len����һ�����ַ�λ��('\0')
	char *base64Buf = new char[base64Len];
	if (base64Buf == NULL) return ENC_MEMORY_ERR;
	ZeroMemory(base64Buf, base64Len);
	Base64::binToBase64((unsigned char*)outBuf, base64Buf, outLen);

	ofstream fout(outFile);
	if (!fout) return ENC_FILE_ERR;
	fout << base64Buf;
	fout.close();


	delete[] base64Buf;
	delete[] outBuf;

	return ENC_OK;
}



//--------------------------------------------------------------------
//������ �� DecFile
//������������ �������ļ�
//�������� ��inFile�����ļ���, outFile�����ļ��� KEY-16�ֽ���Կ 
//��������ֵ �� 0�ɹ� -1�ļ��򿪴� -2�ڴ�������
//���� �������
//������������ �� 2016-8-23
//�����޸����� ��  2016-8-26
//�޸��� �������
//�޸�ԭ�� �� 
//�汾 �� 1.02
//��ʷ�汾 �� 1.01
//--------------------------------------------------------------------
int DecFile(const char *inFile, const char *outFile, const char *KEY)
{
	ifstream fin(inFile);
	if (!fin) return ENC_FILE_ERR;

	fin.seekg(0, ios::end);   
	int fileSize  = fin.tellg();  
	fin.seekg(0, ios::beg);
	fin.read(g_inBuf, fileSize);
	fin.close();

	AesCipher crypto;
	char counter[16] = {0};
	counter[5] = -113;
	crypto.makeRoundKey(KEY, 16); 
	crypto.setCounter(counter);

	// BASE64����
	int tempLen = strlen(g_inBuf);
	int base64Len = tempLen;
	int outLen = Base64::calculateBinLen(base64Len); 
	outLen = outLen / 16 * 16;  //��Ϊbase64�����ַ��������ȡ�������ܺ�ĳ���
	char *outBuf = new char[outLen+1];
	if (outBuf == NULL) return ENC_MEMORY_ERR;
	ZeroMemory(outBuf, outLen+1);
	int temLen = Base64::base64ToBin(g_inBuf, (unsigned char*)outBuf, outLen);

	// AES����
	char *out2 = new char[outLen+1];
	if (out2 == NULL) return ENC_MEMORY_ERR;
	ZeroMemory(out2, outLen+1);
	int plainTextLen = crypto.decryptString(outBuf, out2, outLen, AesCipher::CTR); 
	out2[plainTextLen] = '\0';

	ofstream fout(outFile);
	if (!fout) return ENC_FILE_ERR;
	fout << out2;
	fout.close();


	delete[] outBuf;
	delete[] out2;

	return ENC_OK;
}