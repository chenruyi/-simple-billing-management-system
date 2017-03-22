#include "deposit_return_service.h"
#include"global.h"
#include <iostream>
#include<iomanip>
#include<fstream>
#include"time_string.h"
#include"writeusinginfo.h"
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
		cout << "���ļ�ʧ�ܣ���" << endl;
		return false;
	}
	while (!file.eof())
	{
		file.getline(card_temp->aName, NAME_MAX, '\t');

		if (strcmp(card_temp->aName, card_deposit.aName) == 0)
		{
			file.ignore(10,'\t');//����card->nPsw
		
			file.ignore(3, '\t');//����card->nstatus
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			file << setiosflags(ios::fixed) << setprecision(2)
				<< card_deposit.fBalance + deposit_money<<flush;
			file.ignore(2, '\t');//����'\t'
		
			file.ignore(10, '\t');//����ʹ���ܶ�card->fAmount
			
			file.ignore(10, '\t');//����card->nUsecount
			file.ignore(3, '\t');//����card->ndel
			
			file.ignore(TIMELENGTH, '\t');//����card->tstart
			
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			timeToString(card_deposit.tLast, time_last);
			file << time_last<<flush;
			//�ϴ�ʹ��ʱ����£�
			flag = true;
			break;
		}
		file.getline(rest, 512, '\n');
	}
	file.close();
	usingInfo info;
	strcpy_s(info.aName, card_deposit.aName);
	info.operatekind = O_deposit;//��ֵ��
	info.fBalance = card_deposit.fBalance;
	info.operate_time = card_deposit.tLast;
	writeusinginfo(info);
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
		cout << "���ļ�ʧ�ܣ���" << endl;
		return false;
	}
	while (!file.eof())
	{
		file.getline(card_temp->aName, NAME_MAX, '\t');

		if (strcmp(card_temp->aName, card_return.aName) == 0)
		{
			file.ignore(10, '\t');//����card->nPsw
			
			file.ignore(3, '\t');//����card->nstatus
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			file << 0 << flush;//��������Ϊ0
			file.ignore(2, '\t');//����'\t'
			file.ignore(10, '\t');//����ʹ���ܶ�card->fAmount
			file.ignore(10, '\t');//����card->nUsecount
			file.ignore(3, '\t');//����card->ndel
								 //file.getline(ndel, 2, '\t');
			file.ignore(TIMELENGTH, '\t');//����card->tstart
										  //file.getline(time_start, TIMELENGTH, '\t');
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			timeToString(card_return.tLast, time_last);
			file << time_last << flush;
			//�ϴ�ʹ��ʱ����£�
			flag = true;
			break;
		}
		file.getline(rest, 512, '\n');
	}
	file.close();
	usingInfo info;
	strcpy_s(info.aName, card_return.aName);
	info.operatekind = O_return;//�˷�
	info.fBalance = card_return.fBalance;
	info.operate_time = card_return.tLast;
	writeusinginfo(info);
	return flag;
}
