// CodeTool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <assert.h>
#include "EasyUltils.h"

using namespace EASY_UlTILS;
using namespace std;
using namespace std;


void Test1()
{
	assert(FormatString("%d", 123) == "123");
	assert(FormatString("%s", "happy123") == "happy123");
	assert(FormatString("%.02f", 12.34) == "12.34");
}


int _tmain(int argc, _TCHAR* argv[])
{
	cout << GetAppPathA() << endl;
	cout << FormatString("%f", 12.34f) << endl;

	Test1();


	getchar();
	return 0;
}

