#include "deposit_return_service.h"
#include"global.h"
#include <iostream>
#include<fstream>
#include"time_string.h"
using namespace std;
bool Deposit(Card card_deposit, float deposit_money)
{
	char *time_last = (char *)malloc(sizeof(char));
	const char* path = "card.txt";
	Card *card_temp=(Card*)malloc(sizeof(Card));
	char rest[512];
	bool flag = false;
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

		if (strcmp(card_temp->aName, card_deposit.aName) == 0)
		{
			file.ignore(10,'\t');//跳过card->nPsw
			//file.getline(card_temp.aPwd, PSD_MAX, '\t');
			//file.seekp(1, ios::cur);
			//file.seekp(-1, ios::cur);
			//file << 1;//上机,card->ndel=1
			//file.flush();
			file.ignore(3, '\t');//跳过card->nstatus
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			file << card_deposit.fBalance + deposit_money<<flush;
			file.ignore(2, '\t');//跳过'\t'
			//file.getline(balance, sizeof(float), '\t');
			//file.getline(amount, sizeof(float), '\t');
			//file << cardin.fAmount;
			file.ignore(10, '\t');//跳过使用总额card->fAmount
			//file.getline(usecount, 10, '\t');
			//file.seekp(1, ios::cur);
			//file.seekp(-1, ios::cur);
			//file << card_deposit.nUseCount;//更新使用次数
			//file.flush();
			file.ignore(10, '\t');//跳过card->nUsecount
			file.ignore(3, '\t');//跳过card->ndel
			//file.getline(ndel, 2, '\t');
			file.ignore(TIMELENGTH, '\t');//跳过card->tstart
			//file.getline(time_start, TIMELENGTH, '\t');
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			timeToString(card_deposit.tLast, time_last);
			file << time_last<<flush;
			//上次使用时间更新；
			file.flush();
			flag = true;
			break;
		}
		file.getline(rest, 512, '\n');
	}
	file.close();
	return flag;
}

bool Return(Card card_return)
{

	char *time_last = (char *)malloc(sizeof(char));
	const char* path = "card.txt";
	Card *card_temp = (Card*)malloc(sizeof(Card));
	char rest[512];
	bool flag = false;
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

		if (strcmp(card_temp->aName, card_return.aName) == 0)
		{
			file.ignore(10, '\t');//跳过card->nPsw
			
			file.ignore(3, '\t');//跳过card->nstatus
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			file << 0 << flush;//将余额更新为0
			file.ignore(2, '\t');//跳过'\t'
			file.ignore(10, '\t');//跳过使用总额card->fAmount
			file.ignore(10, '\t');//跳过card->nUsecount
			file.ignore(3, '\t');//跳过card->ndel
								 //file.getline(ndel, 2, '\t');
			file.ignore(TIMELENGTH, '\t');//跳过card->tstart
										  //file.getline(time_start, TIMELENGTH, '\t');
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			timeToString(card_return.tLast, time_last);
			file << time_last << flush;
			//上次使用时间更新；
			file.flush();
			flag = true;
			break;
		}
		file.getline(rest, 512, '\n');
	}
	file.close();
	return flag;
}
