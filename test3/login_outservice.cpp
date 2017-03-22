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
	//��ȡ����Ϣ���ӵ���ʱ����
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
		cout << "���ļ�ʧ�ܣ���" << endl;
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
			file << 1<<flush;//�ϻ�,card->ndel=1
			//ʹ�ô���+1��
			file.ignore(2, '\t');//����'\t'
			file.ignore(10, '\t');//����card->Bbalance
			//file.getline(balance, sizeof(float), '\t');
			//file.getline(amount, sizeof(float), '\t');
			//file << cardin.fAmount;
			file.ignore(10, '\t');//����ʹ���ܶ�card->fAmount
			//file.getline(usecount, 10, '\t');
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			file << cardin.nUseCount<<flush;//����ʹ�ô���
	
			file.ignore(2, '\t');//����'\t'
			file.ignore(2, '\t');//����card->ndel
			//file.getline(ndel, 2, '\t');
			file.ignore(TIMELENGTH, '\t');//����card->tstart
			//file.getline(time_start, TIMELENGTH, '\t');
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			timeToString(cardin.tLast, time_last);
			file << time_last<<flush;
			//�ϴ�ʹ��ʱ����£�
			file.flush();
			flag = true;
			break;
		}
		file.getline(rest, 512, '\n');
	}
	file.close();
	usingInfo info;
	strcpy_s(info.aName, cardin.aName);
	info.operatekind = O_login;//�ϻ�
	info.fBalance = cardin.fBalance;
	info.operate_time = cardin.tLast;
	writeusinginfo(info);
	return flag;
}

bool logout(Card &cardout)
{
	//��ȡ����Ϣ���ӵ���ʱ����
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
		cout << "���ļ�ʧ�ܣ���" << endl;
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
			file << 0;//�»�,card->ndel=0	
			file.flush();
			file.ignore(2, '\t');//����'\t'
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			file << setiosflags(ios::fixed) << setprecision(2) << cardout.fBalance;
			file.flush();
			file.ignore(10, '\t');//����card->Bbalance
			//file.getline(balance, sizeof(float), '\t');
			//file.getline(amount, sizeof(float), '\t');
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			file << cardout.fAmount;//����ʹ���ܶ�card->fAmount
			file.flush();
			file.ignore(2, '\t');//����'\t'
			//file.getline(usecount, 10, '\t');
			//file << cardout.nUseCount;//����ʹ�ô���
			file.ignore(10, '\t');//����card->nUsecount
			file.ignore(2, '\t');//����card->ndel
			//file.getline(ndel, 2, '\t');
			file.ignore(TIMELENGTH, '\t');//����card->tstart
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
	info.operatekind = O_logout;//�»�
	info.fBalance = cardout.fBalance;
	info.operate_time = cardout.tLast;
	writeusinginfo(info);
	return flag;
}
