#include "statistic.h"
#include "global.h"
#include"time_string.h"
#include<iostream>
#include<fstream>
using namespace std;
float S_Sumpay(void)
{
	float summoney = 0.0f;
	float everymoney = 0.0f;
	const char* path = "card.txt";
	char usingcount[10];
	
	ifstream file(path, ios::in);
	if (!file.is_open())
	{
		cout << "文件打开失败";
	}
	while (!file.eof())
	{
		file.ignore(NAME_MAX, '\t');//card.aName
		file.ignore(PSD_MAX, '\t');//card.aPwd
		file.ignore(2, '\t');// card.nStatus 
		file.ignore(10, '\t');//card.fBalance
		file.get(usingcount, '\t');
		everymoney = atof(usingcount);
		summoney += everymoney;
		file.ignore( 1024, '\n');
		
	}
	file.close();

	return summoney;
}

Card * S_CardNum(int & n)
{
	const char* path = "card.txt";
	ifstream file(path, ios::in);
	if (!file.is_open())
	{
		cout << "文件打开失败";
	}
	while (!file.eof())
	{
		file.ignore(NAME_MAX, '\t');//card.aName
		n++;
		file.ignore(1024, '\n');

	}
	file.close();

	return nullptr;
}
