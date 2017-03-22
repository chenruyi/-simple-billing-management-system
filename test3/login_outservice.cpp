#include "login_outservice.h"
#include"global.h"
#include"time_string.h"
#include"writeusinginfo.h"
#include<iostream>
#include <fstream>
#include<iomanip>
using namespace std;
bool login(Card cardin)
{
	//读取卡信息增加的临时变量
	char time_last[TIMELENGTH];//card->tLast
	

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
			file << 1<<flush;//上机,card->ndel=1
			//使用次数+1；
			file.ignore(2, '\t');//跳过'\t'
			file.ignore(10, '\t');//跳过card->Bbalance
			//file.getline(balance, sizeof(float), '\t');
			//file.getline(amount, sizeof(float), '\t');
			//file << cardin.fAmount;
			file.ignore(10, '\t');//跳过使用总额card->fAmount
			//file.getline(usecount, 10, '\t');
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			file << cardin.nUseCount<<flush;//更新使用次数
	
			file.ignore(2, '\t');//跳过'\t'
			file.ignore(2, '\t');//跳过card->ndel
			//file.getline(ndel, 2, '\t');
			file.ignore(TIMELENGTH, '\t');//跳过card->tstart
			//file.getline(time_start, TIMELENGTH, '\t');
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			timeToString(cardin.tLast, time_last);
			file << time_last<<flush;
			//上次使用时间更新；
			file.flush();
			flag = true;
			break;
		}
		file.getline(rest, 512, '\n');
	}
	file.close();
	usingInfo info;
	strcpy_s(info.aName, cardin.aName);
	info.operatekind = O_login;//上机
	info.fBalance = cardin.fBalance;
	info.operate_time = cardin.tLast;
	writeusinginfo(info);
	return flag;
}

bool logout(Card &cardout)
{
	//读取卡信息增加的临时变量
	char time_last[TIMELENGTH];//card->tLast

	Card *card_temp = (Card *)malloc(sizeof(Card));
	bool flag = false;
	const char* path = "card.txt";
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
		file.getline(card_temp->aName, NAME_MAX, '\t');

		if (strcmp(card_temp->aName, cardout.aName) == 0)
		{
			file.getline(card_temp->aPwd, PSD_MAX, '\t');
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			file << 0;//下机,card->ndel=0	
			file.flush();
			file.ignore(2, '\t');//跳过'\t'
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			file << setiosflags(ios::fixed) << setprecision(2) << cardout.fBalance;
			file.flush();
			file.ignore(10, '\t');//跳过card->Bbalance
			//file.getline(balance, sizeof(float), '\t');
			//file.getline(amount, sizeof(float), '\t');
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			file << cardout.fAmount;//更新使用总额card->fAmount
			file.flush();
			file.ignore(2, '\t');//跳过'\t'
			//file.getline(usecount, 10, '\t');
			//file << cardout.nUseCount;//更新使用次数
			file.ignore(10, '\t');//跳过card->nUsecount
			file.ignore(2, '\t');//跳过card->ndel
			//file.getline(ndel, 2, '\t');
			file.ignore(TIMELENGTH, '\t');//跳过card->tstart
			//file.getline(time_start, TIMELENGTH, '\t');
			timeToString(cardout.tLast, time_last);
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			file << time_last;
			file.flush();
			flag = true;
			break;
		}
		file.getline(rest, 512, '\n');
	}
	file.close();
	usingInfo info;
	strcpy_s(info.aName, cardout.aName);
	info.operatekind = O_logout;//下机
	info.fBalance = cardout.fBalance;
	info.operate_time = cardout.tLast;
	writeusinginfo(info);
	return flag;
}
