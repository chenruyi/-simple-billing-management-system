#include <iostream>
#include"struct.h"
#include"cardservice_doc.h"
#include "time_string.h"
#include"writeusinginfo.h"
#include <fstream>
#include"global.h"
using namespace std;
bool AddCard(Card card)//���ӿ�
{
	bool flag = false;
	Card card_temp;
	const char* path = "card.txt";
	char rest[512];
	ifstream fin(path,ios::in);
	ofstream fout(path, ios::app);
	if (!fin.is_open()||!fout.is_open())
	{
		cout << "���ļ�ʧ�ܣ���"<<endl;
		return false;
	}
	while(!fin.eof())
	{
		fin.getline(card_temp.aName, NAME_MAX, '\t');		
		
			if (strcmp(card_temp.aName, card.aName) == 0)
			{
				cout << "�����Ѵ��ڣ���" << endl;
				return false;
			}
			fin.getline(rest, 512, '\n');
		
	}
	char time_end[TIMELENGTH];
	char time_start[TIMELENGTH];
	char time_last[TIMELENGTH];
	timeToString(card.tEnd, time_end);
	timeToString(card.tStart, time_start);
	timeToString(card.tLast, time_last);
	fin.close();
	fout << card.aName << '\t' << card.aPwd << '\t'
		<< card.nStatus << '\t' << card.fBalance << '\t'
		<< card.fAmount << '\t' << card.nUseCount << '\t'
		<< card.nDel << '\t' << time_start << '\t'
		<< time_last << '\t' << time_end << '\n';
	fout.close();	
	usingInfo info;
	strcpy_s(info.aName, card.aName);
	info.fBalance = card.fBalance;
	info.nStatus = card.nStatus;
	info.operate_time = card.tLast;
	if (writeusinginfo(info))
	{
		flag = true;
	}
	else
	{
		flag = false;
	}
	return flag;

}
bool DeleteCard(Card card_delete)//ע����
{
	bool flag = false;
	Card card_temp;
	char *time_end = (char*)malloc(sizeof(char));
	timeToString(card_delete.tEnd, time_end);
	const char* path = "card.txt";
	char rest[512];
	fstream file(path,ios::in|ios::out);
	file.seekg(0);
	file.seekp(0);
	if (!file.is_open() )
	{
		cout << "���ļ�ʧ�ܣ���" << endl;
		return false;
	}
	while(!file.eof())
	{
		file.getline(card_temp.aName, NAME_MAX, '\t');
		
		if (strcmp(card_temp.aName, card_delete.aName) == 0)
		{
			file.getline(card_temp.aPwd, PSD_MAX, '\t');
			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			file << 2<<flush;//ע��,card->nstatus=2	
			file.ignore(20, '\t');//����card->fbalance
			file.ignore(20, '\t');//����card->famount
			file.ignore(20, '\t');//����card->nusecount
			file.ignore(20, '\t');//����card->ndel
			file.ignore(20, '\t');//����card->start
			file.ignore(20, '\t');//����card->last

			file.seekp(1, ios::cur);
			file.seekp(-1, ios::cur);
			file << time_end << flush;//ע��,card->nstatus=2		
			flag = true;
			break;
		}
		file.getline(rest, 512, '\n');
	}
	file.close();
	return flag;
}
Card *SelectCard(char *aName) {
	
	Card *card = (Card*)malloc(sizeof(Card));
	char rest[1024];
	char nstat[2];//card->nstatus�Ĵ���
	char ndel[2];//card->nDel
	char usecount[10];//card->nUseCount
	char time_start[TIMELENGTH];//card->tStart
	char time_end[TIMELENGTH];//card->tEnd
	char time_last[TIMELENGTH];//card->tLast
	char balance[20];//card->fBalance
	char amount[20];//card->fAmount
	ifstream file("card.txt", ios::in);
	if (!file.is_open())
	{
		cout << "�ļ���ʧ�ܣ���" << endl;
	}
	while (!file.eof())
	{
		file.getline(card->aName, NAME_MAX, '\t');//����
		if (strcmp(card->aName, aName) == 0)
		{
			file.getline(card->aPwd, PSD_MAX, '\t');//����
			file.getline(nstat, 2, '\t'); card->nStatus = nstat[0] - '0';//״̬
			file.getline(balance, 20, '\t');
			sscanf_s(balance, "%f", &card->fBalance);
			file.getline(amount, 20, '\t');
			sscanf_s(amount, "%f", &card->fAmount);
			file.getline(usecount, 10, '\t');
			sscanf_s(usecount, "%d", &card->nUseCount);
			file.getline(ndel, 2, '\t');
			sscanf_s(ndel, "%d", &card->nDel);
			file.getline(time_start, TIMELENGTH, '\t');
			card->tStart = stringToTime(time_start);
			file.getline(time_last, TIMELENGTH, '\t');
			card->tLast = stringToTime(time_last);
			file.getline(time_end, TIMELENGTH, '\t');
			card->tEnd = stringToTime(time_end);
			break;
		}
		else
		{
			file.getline(rest, 1024, '\n');
		}

		
	}
	file.close();
	
	return card;
}