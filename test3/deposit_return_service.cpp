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
		cout << "���ļ�ʧ�ܣ���" << endl;
		return false;
	}
	while (!file.eof())
	{
		file.getline(card_temp->aName, NAME_MAX, '\t');

		if (strcmp(card_temp->aName, card_deposit.aName) == 0)
		{
			file.ignore(10,'\t');//����card->nPsw
			//file.getline(card_temp.aPwd, PSD_MAX, '\t');
			//file.seekp(1, ios::cur);
			//file.seekp(-1, ios::cur);
			//file << 1;//�ϻ�,card->ndel=1
			//file.flush();
			file.ignore(3, '\t');//����card->nstatus
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			file << card_deposit.fBalance + deposit_money<<flush;
			file.ignore(2, '\t');//����'\t'
			//file.getline(balance, sizeof(float), '\t');
			//file.getline(amount, sizeof(float), '\t');
			//file << cardin.fAmount;
			file.ignore(10, '\t');//����ʹ���ܶ�card->fAmount
			//file.getline(usecount, 10, '\t');
			//file.seekp(1, ios::cur);
			//file.seekp(-1, ios::cur);
			//file << card_deposit.nUseCount;//����ʹ�ô���
			//file.flush();
			file.ignore(10, '\t');//����card->nUsecount
			file.ignore(3, '\t');//����card->ndel
			//file.getline(ndel, 2, '\t');
			file.ignore(TIMELENGTH, '\t');//����card->tstart
			//file.getline(time_start, TIMELENGTH, '\t');
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			timeToString(card_deposit.tLast, time_last);
			file << time_last<<flush;
			//�ϴ�ʹ��ʱ����£�
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
			file.flush();
			flag = true;
			break;
		}
		file.getline(rest, 512, '\n');
	}
	file.close();
	return flag;
}
