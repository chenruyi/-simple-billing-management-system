#pragma once
/*
�������˵�
ʱ�䣺2017/2/22
�汾��1.0
*/

#include "iostream"
#include "struct.h"
#include "cardservice.h"
#include "cardservice_doc.h"
#include"global.h"
#include "time_string.h"
#include"login_outservice.h"
#include"billingservice.h"
using namespace std;
//--------1.���ӿ�---------
void AddCard_Menu(void) {
	bool flag = false;
	Card card = { '\0' };
	cout << "----------���ӿ�----------" << endl;
	cout << "�����뿨��: ";
	cin >> card.aName;
	cout << "���������룺";
	cin >> card.aPwd;
	cout << "�����뿪����";
	cin >> card.fBalance;
	card.fAmount = 0;
	card.nUseCount = 0;
	card.nStatus = 0;
	card.nDel = 0;
	card.tStart = card.tEnd = card.tLast = time(NULL);

	flag = AddCard(card);
	if (flag)
	{
		cout << "�����û��ɹ�!!" << "\n"
			<< "����\t����\t״̬\t���" << "\n"
			<< card.aName << "\t" << card.aPwd << "\t"
			<< card.nStatus << "\t" << card.fBalance
			<< endl;
	}
	else
	{
		cout << "�����û�ʧ�ܣ���" << endl;
	}

}

//-----------2.��ѯ��----------
void SelectCard_Menu() {
	char aName[NAME_MAX];//����
	Card* card ;
	Card card_[CARD_USINGMAX] = { NULL };
	int n = 0;
	cout << "----------��ѯ��----------" << endl;
	cout << "�����뿨�ţ�";
	cin >> aName;
	//card = SelectCard(aName,n);
	card = SelectCard(aName);
	if (card != NULL)//&&n!=0)
	{
		/*	for (int i = 0; i < n; i++,card++)
		{*/
		char Lasttime[TIMELENGTH] ;
		timeToString(card->tLast, Lasttime);
		int j = 0;
		cout << "��ѯ�����" << "\n"
			<< "����\t״̬\t���\tʹ�ô���\t�ϴ�ʹ��ʱ��" << "\n"
			<< card->aName << "\t" << card->nStatus << "\t"
			<< card->fBalance << "\t" << card->nUseCount << "\t\t"
			<< Lasttime << endl;

		//}
	}
	else {
		cout << "δ�鵽����" << endl;
	}
}

//----------3.�ϻ�---------  
void On_comp_Menu()
{
	Card *card = (Card*)malloc(sizeof(Card));

	cout << "----------�ϻ�----------" << endl;
	cout << "�����뿨�ţ�";
	cin >> card->aName;
	card = SelectCard(card->aName);
	if (card == NULL)
	{
		cout << "δ�ҵ��ÿ���Ϣ" << endl;
	}
	else if (card->nStatus == 1)
	{
		cout << "�ÿ������ϻ�" << endl;
	}
	else if (card->nStatus == 2)
	{
		cout << "�ÿ���ע��" << endl;
	}
	else if (card->nStatus == 3)
	{
		cout << "�ÿ���ʧЧ" << endl;
	}
	else if (card->nStatus == 0)
	{
		if (card->fBalance > 0)
		{
			cout << "�˻����Ϊ" << card->fBalance << endl;
			if (login(*card))
			{
				cout << "�ϻ��ɹ�������ӭʹ�ã���" << endl;
			}
			else
			{
				cout << "��½ʧ�ܣ�" << endl;

			}

		}
		else
		{
			cout << "�˻����㣬���ֵ" << endl;
		}

	}
}
//----------4.�»�----------
void Off_comp_Menu()
{
	Card *card = (Card*)malloc(sizeof(Card));
	float paymoney = -1;
	cout << "----------�»�----------" << endl;
	cout << "�����뿨�ţ�";
	cin >> card->aName;
	card = (SelectCard(card->aName));
	if (card == NULL)
	{
		cout << "δ�ҵ��ÿ���Ϣ" << endl;
	}
	else if (card->nStatus == 0)
	{
		cout << "�ÿ�δ�ϻ�" << endl;
	}
	else if (card->nStatus == 2)
	{
		cout << "�ÿ���ע��" << endl;
	}
	else if (card->nStatus == 3)
	{
		cout << "�ÿ���ʧЧ" << endl;
	}
	else if (card->nStatus == 1)
	{
		paymoney = PayFee(*card);
		if (card->fBalance < paymoney)
		{
			cout << "����,���ֵ����" << '\n'
				<< "�˻���" << card->fBalance << "Ԫ" << '\n'
				<< "�����轻�ѣ�" << paymoney << "Ԫ" << endl;
		}
		else
		{
			card = logout(*card);
			if (card != NULL)// �˳��ɹ�
			{
				cout << "�˳��ɹ�����" << '\n'
					<< "���νɷѣ�" << paymoney << "Ԫ"
					<< "�˻���" << card->fBalance << "Ԫ" << "\n"
					<< "��ӭ�´�ʹ�ã���" << endl;
			}
			else
			{
				cout << "�˳�ʧ�ܣ��������ԣ���" << endl;
			}
		}
	}

}

//---------5.��ֵ----------
void Deposit_Menu()
{
	Card *card = (Card*)malloc(sizeof(Card));
	int deposit_money;//��ֵ���
	double balance = 100.0;//���
	cout << "---------��ֵ---------" << endl;
	cout << "�������ֵ�Ŀ��ţ�";
	cin >> card->aName;
	cout << "�������ֵ�Ľ�";
	cin >> deposit_money;

	if (true)	//��ֵ�ɹ�
	{
		cout << "��ֵ�ɹ������Ϊ��" << balance << endl;;
	}
	else
	{
		cout << "��ֵʧ��" << endl;
	}
}

//---------6.�˷�----------
void Return_Menu()
{
	Card *card = (Card*)malloc(sizeof(Card));
	int return_money = 0;//�˷ѽ��
	cout << "----------�˷�----------" << endl;
	cout << "�����뿨�ţ�" << endl;
	cin >> card->aName;
	if (true) //���Ŵ���
	{
		cout << "�˷ѽ�" << return_money << endl;
		if (true)//�˷ѳɹ�
		{
			cout << "�˷ѳɹ���" << endl;
		}
		else
		{
			cout << "�˷�ʧ�ܣ�" << endl;
		}
	}
	else
	{
		cout << "���Ų����ڣ�" << endl;
	}
}

//---------7.��ѯͳ��-------
void Statistic_Menu()
{
	cout << "---------��ѯͳ��-------" << "\n"
		<< "1. �������ܶ�" << "\n"
		<< "2. ����"
		<< endl;
}

//---------8.ע����--------
void Delete_Menu()
{
	Card *card = (Card*)malloc(sizeof(Card));
	double balance = 100.0;//���
	cout << "----------ע����----------" << endl;
	cout << "������ע���Ŀ��ţ�";
	cin >> card->aName;
	card = SelectCard(card->aName);
	if (card != NULL)	//�����Ŵ���
	{
		cout << "��ȷ��ע�����ţ�" << card->aName <<"(y/n)��";
		char choice;
		cin >> choice;
		if (choice == 'y' || choice == 'Y')	//ȷ�ϲ���
		{
			if (card->fBalance>=0)	//���>=0
			{
				cout << "�ÿ������Ϊ��" << card->fBalance << endl;
				if (DeleteCard(card->aName))//ע����
				{
					cout << "ע�����ɹ�����" << endl;
				}
				else
				{
					cout << "ע��ʧ��" << endl;
				}
			}
			else		//���<0
			{
				cout << "�ÿ���Ƿ�ѣ�" << balance << "�뽻�ѣ���" << endl;
				//if (true)//�ɷѳɹ�
				//{
				//	cout << "�ɷѳɹ�����" << endl;
				//}
				//else
				//{
				//	cout << "�ɷ�ʧ�ܣ���" << endl;
				//}
			}
		}
		else	//ȡ������
		{
			cout << "ȡ��������" << endl;
		}

	}
	else
	{
		cout << "�ÿ��Ų����ڣ������飡��" << endl;
	}
}

//---------0.�˳�---------
void Logout() {
	cout << "�˳�ϵͳ����ӭ�´�ʹ�ã���" << endl;
	exit(0);
}




void Main_Menu(void)
{
	int choice;
	while (true) {
		cout << "----------�˵�----------" << endl;
		cout << "1.���ӿ�" << "\n"
			<< "2.��ѯ��" << "\n"
			<< "3.�ϻ�  " << "\n"
			<< "4.�»�  " << "\n"
			<< "5.��ֵ  " << "\n"
			<< "6.�˷�  " << "\n"
			<< "7.��ѯͳ��" << "\n"
			<< "8.ע����" << "\n"
			<< "0.�˳�  " << endl;
		cout << "----------------------" << endl;
		cout << "��ѡ��˵�����(0-8):";
		cin >> choice;
		switch (choice) {
		case 1:			//1.���ӿ�
		{
			AddCard_Menu();
			break;
		}
		case 2:			//2.��ѯ��
		{
			SelectCard_Menu();
			break;
		}
		case 3:			//3.�ϻ�  
		{
			On_comp_Menu();
			break;
		}
		case 4:			//4.�»�
		{
			Off_comp_Menu();
			break;
		}
		case 5:			//5.��ֵ
		{
			Deposit_Menu();
			break;
		}
		case 6:			//6.�˷�
		{
			Return_Menu();
			break;
		}
		case 7:			//7.��ѯͳ��
		{
			Statistic_Menu();
			break;
		}
		case 8:			//8.ע����
		{
			Delete_Menu();
			break;
		}
		case 0:			//0.�˳�
		{
			Logout();
			break;
		}
		default:
		{
			cout << "��ѡ�����ڣ�������ѡ�񣡣�" << endl;
			continue;
		}
		}

	}
}