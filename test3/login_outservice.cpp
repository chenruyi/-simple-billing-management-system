#include "login_outservice.h"
#include"global.h"
#include"time_string.h"
#include<iostream>
#include <fstream>
using namespace std;
bool login(Card cardin)
{
	bool flag = false;
	const char* path = "card.txt";
	Card card_temp;
	char rest[512];
	fstream file(path, ios::in | ios::out);
	file.seekg(0);
	file.seekp(0);
	if (!file.is_open())
	{
		cout << "打开文件失败！！" << endl;
		return false;
	}
	while (!file.eof())
	{
		file.getline(card_temp.aName, NAME_MAX, '\t');

		if (strcmp(card_temp.aName, cardin.aName) == 0)
		{
			file.getline(card_temp.aPwd, PSD_MAX, '\t');
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			file << 1;//上机,card->ndel=1	
			file.flush();
			flag = true;
			break;
		}
		file.getline(rest, 512, '\n');
	}
	file.close();
	return flag;
}

Card * logout(Card cardout)
{
	bool flag = false;
	const char* path = "card.txt";
	Card card_temp;
	char rest[512];
	fstream file(path, ios::in | ios::out);
	file.seekg(0);
	file.seekp(0);
	if (!file.is_open())
	{
		cout << "打开文件失败！！" << endl;
		return false;
	}
	while (!file.eof())
	{
		file.getline(card_temp.aName, NAME_MAX, '\t');

		if (strcmp(card_temp.aName, cardout.aName) == 0)
		{
			file.getline(card_temp.aPwd, PSD_MAX, '\t');
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			file << 0;//下机,card->ndel=0	
			file.flush();
			flag = true;
			break;
		}
		file.getline(rest, 512, '\n');
	}
	file.close();
	return &card_temp;
}
