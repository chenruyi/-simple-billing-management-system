#pragma once
/*
描述：菜单
时间：2017/2/22
版本：1.0
*/

#include "iostream"
#include "struct.h"
#include "cardservice.h"
#include "cardservice_doc.h"
#include"global.h"
#include "time_string.h"
#include"login_outservice.h"
#include"billingservice.h"
#include"deposit_return_service.h"
#include"statistic.h"
#include <iomanip>
using namespace std;
//--------1.添加卡---------
void AddCard_Menu(void) {
	bool flag = false;
	Card card = { '\0' };
	cout << "----------添加卡----------" << endl;
	cout << "请输入卡号: ";
	cin >> card.aName;
	cout << "请输入密码：";
	cin >> card.aPwd;
	cout << "请输入开户金额：";
	cin >> card.fBalance;
	card.fAmount = 0;
	card.nUseCount = 0;
	card.nStatus = 0;
	card.nDel = 0;
	card.tStart = card.tEnd = card.tLast = time(NULL);

	flag = AddCard(card);
	if (flag)
	{
		cout << "添加用户成功!!" << "\n"
			<< "卡号\t密码\t状态\t余额" << "\n"
			<< card.aName << "\t" << card.aPwd << "\t"
			<< card.nStatus << "\t" << card.fBalance
			<< endl;
	}
	else
	{
		cout << "添加用户失败！！" << endl;
	}

}

//-----------2.查询卡----------
void SelectCard_Menu() {
	char aName[NAME_MAX];//卡号
	Card* card ;
	
	int n = 0;
	cout << "----------查询卡----------" << endl;
	cout << "请输入卡号：";
	cin >> aName;
	//card = SelectCard(aName,n);
	card = SelectCard(aName);
	if (card != NULL)//&&n!=0)
	{
		char Lasttime[TIMELENGTH] ;
		timeToString(card->tLast, Lasttime);
		int j = 0;
		cout << "查询结果：" << "\n"
			<< "卡号\t状态\t余额\t使用次数\t上次使用时间" << "\n"
			<< card->aName << "\t" << card->nStatus << "\t"
			<< setiosflags(ios::fixed) << setprecision(2) << card->fBalance << "\t"
			<< card->nUseCount << "\t\t"
			<< Lasttime << endl;
	}
	else {
		cout << "未查到！！" << endl;
	}
}

//----------3.上机---------  
void On_comp_Menu()
{
	Card *card = (Card*)malloc(sizeof(Card));
	char card_name[NAME_MAX];
	char card_psw[PSD_MAX];
	cout << "----------上机----------" << endl;
	cout << "请输入卡号：";
	cin >> card_name;
	cout << "请输入密码：";
	cin >> card_psw;
	card = SelectCard(card_name);
	if (card == NULL)
	{
		cout << "未找到该卡信息" << endl;
	}
	else if (strcmp(card->aPwd,card_psw)!=0)
	{
		cout << "密码不匹配" << endl;
	}
	else if (card->nStatus == 1)
	{
		cout << "该卡正在上机" << endl;
	}
	else if (card->nStatus == 2)
	{
		cout << "该卡已注销" << endl;
	}
	else if (card->nStatus == 3)
	{
		cout << "该卡已失效" << endl;
	}
	else if (card->nStatus == 0)
	{
		if (card->fBalance > 0)
		{
			cout << "账户余额为:" 
				<< setiosflags(ios::fixed) << setprecision(2) << card->fBalance << endl;
			card->nUseCount++;//使用次数加1；
			card->tLast = time(NULL);//获得上机时间
			if (login(*card))
			{
				cout << "上机成功！！欢迎使用！！" << endl;
			}
			else
			{
				cout << "登陆失败！" << endl;

			}

		}
		else
		{
			cout << "账户余额不足，请充值" << endl;
		}

	}
}
//----------4.下机----------
void Off_comp_Menu()
{
	Card *card = (Card*)malloc(sizeof(Card));
	char card_name[NAME_MAX];
	float paymoney = -1;
	cout << "----------下机----------" << endl;
	cout << "请输入卡号：";
	cin >> card_name;
	
	card = (SelectCard(card_name));
	if (card == NULL)
	{
		cout << "未找到该卡信息" << endl;
	}
	else if (card->nStatus == 0)
	{
		cout << "该卡未上机" << endl;
	}
	else if (card->nStatus == 2)
	{
		cout << "该卡已注销" << endl;
	}
	else if (card->nStatus == 3)
	{
		cout << "该卡已失效" << endl;
	}
	else if (card->nStatus == 1)
	{
		paymoney = PayFee(*card);
		if (card->fBalance < paymoney)
		{
			cout << "余额不足,请充值！！" << '\n'
				<< "账户余额：" 
				<< setiosflags(ios::fixed) << setprecision(2) << card->fBalance << "元" << '\n'
				<< "本次需交费：" << paymoney << "元" << endl;
		}
		else
		{
			card->tLast = time(NULL);//获得下机时间
			card->fBalance = card->fBalance - paymoney;
			
			if (logout(*card))// 退出成功
			{
				cout << "退出成功！！" << '\n'
					<< "本次缴费：" << setiosflags(ios::fixed) << setprecision(2)
					<< paymoney << "元"
					<< "账户余额：" << setiosflags(ios::fixed) << setprecision(2)
					<< card->fBalance << "元" << "\n"
					<< "欢迎下次使用！！" << endl;
			}
			else
			{
				cout << "退出失败！！请重试！！" << endl;
			}
		}
	}

}

//---------5.充值----------
void Deposit_Menu()
{
	Card *card = (Card*)malloc(sizeof(Card));
	float deposit_money;//充值金额
	cout << "---------充值---------" << endl;
	cout << "请输入充值的卡号：";
	cin >> card->aName;
	cout << "请输入充值的金额：";
	cin >> deposit_money;
	card = SelectCard(card->aName);
	if (card == NULL)
	{
		cout << "该卡不存在，请检查后再次充值；" << endl;
	}
	else 	
	{
		if (Deposit(*card, deposit_money))
		{
			card = SelectCard(card->aName);
			cout << "充值成功！" << endl;
			cout<< "卡号\t状态\t余额\t使用次数\t" << "\n"
				<< card->aName << "\t" << card->nStatus << "\t"
				<< setiosflags(ios::fixed) << setprecision(2) << card->fBalance << "\t" 
				<< card->nUseCount << "\t\t"
				<< endl;
		}
		else
		{
			cout << "充值失败" << endl;
		}
	}
	
}

//---------6.退费----------
void Return_Menu()
{
	Card *card = (Card*)malloc(sizeof(Card));
	char card_name[NAME_MAX];
	char card_psw[PSD_MAX];
	cout << "----------退费----------" << endl;
	cout << "请输入卡号：";
	cin >> card_name;
	cout << "请输入密码：";
	cin >> card_psw;
	card = SelectCard(card_name);
	if (card == NULL)
	{
		cout << "未找到该卡信息" << endl;
	}
	else if (strcmp(card->aPwd, card_psw) != 0)
	{
		cout << "密码不匹配" << endl;
	}
	else if (card->nStatus == 1)
	{
		cout << "该卡正在上机" << endl;
	}
	else if (card->nStatus == 2)
	{
		cout << "该卡已注销" << endl;
	}
	else if (card->nStatus == 3)
	{
		cout << "该卡已失效" << endl;
	}
	else
	{
		cout << "当前余额为："
			<< setiosflags(ios::fixed) << setprecision(2) << card->fBalance << "元" << endl;
		if (card->fBalance > 0)
		{
			if (Return(*card))
			{
				cout << "退费成功" << endl;
			}
			else
			{
				cout << "退费失败" << endl;
			}
		}
		else
		{
			cout << "余额为负数，请充值！！" << endl;
		}
	}
}

//---------7.查询统计-------
void Statistic_Menu()
{
	int choice;
	cout << "---------查询统计-------" << "\n"
		<< "1. 消费总额" << "\n"
		<< "2. 卡总数"<<"\n"
		<< "3. 消费总额最高的卡"
		<< endl;
	cin >> choice;
	switch (choice)	
	{
		case 1:
		{
			float summoney;//消费总额
			summoney=S_Sumpay();//查询消费总额
			cout << "消费总额为：" 
				<< setiosflags(ios::fixed) << setprecision(2) << summoney << "元" << endl;
			break;
		}
		case 2:
		{
			int cardnum;//卡总数
			S_CardNum(cardnum);
			cout << "卡总数为：" << cardnum << endl;
			break;
		}
		default:
		{
			cout << "所选不存在！！" << endl;
			break;
		}
	}

}

//---------8.注销卡--------
void Delete_Menu()
{
	Card *card = (Card*)malloc(sizeof(Card));
	double balance = 100.0;//余额
	cout << "----------注销卡----------" << endl;
	cout << "请输入注销的卡号：";
	cin >> card->aName;
	card = SelectCard(card->aName);
	if (card == NULL)
	{
		cout << "未找到该卡信息" << endl;
	}
	else if (card->nStatus == 1)
	{
		cout << "该卡正在上机" << endl;
	}
	else if (card->nStatus == 2)
	{
		cout << "该卡已注销" << endl;
	}
	else if (card->nStatus == 3)
	{
		cout << "该卡已失效" << endl;
	}
	else 
	{
		cout << "请确认注销卡号：" << card->aName <<"(y/n)：";
		char choice;
		cin >> choice;
		if (choice == 'y' || choice == 'Y')	//确认操作
		{
			if (card->fBalance>=0)	//余额>=0
			{
				cout << "该卡号余额为：" << card->fBalance << endl;
				card->tEnd = time(NULL);
				if (DeleteCard(*card))//注销卡
				{
					cout << "注销卡成功！！" << endl;
				}
				else
				{
					cout << "注销失败" << endl;
				}
			}
			else		//余额<0
			{
				cout << "该卡号欠费：" << balance << "请交费！！" << endl;
			}
		}
		else	//取消操作
		{
			cout << "取消操作！" << endl;
		}

	}
	
}

//---------0.退出---------
void Logout() {
	cout << "退出系统，欢迎下次使用！！" << endl;
	exit(0);
}




void Main_Menu(void)
{
	int choice;
	while (true) {
		cout << "----------菜单----------" << endl;
		cout << "1.添加卡" << "\n"
			<< "2.查询卡" << "\n"
			<< "3.上机  " << "\n"
			<< "4.下机  " << "\n"
			<< "5.充值  " << "\n"
			<< "6.退费  " << "\n"
			<< "7.查询统计" << "\n"
			<< "8.注销卡" << "\n"
			<< "0.退出  " << endl;
		cout << "----------------------" << endl;
		cout << "请选择菜单项编号(0-8):";
		cin >> choice;
		switch (choice) {
		case 1:			//1.添加卡
		{
			AddCard_Menu();
			break;
		}
		case 2:			//2.查询卡
		{
			SelectCard_Menu();
			break;
		}
		case 3:			//3.上机  
		{
			On_comp_Menu();
			break;
		}
		case 4:			//4.下机
		{
			Off_comp_Menu();
			break;
		}
		case 5:			//5.充值
		{
			Deposit_Menu();
			break;
		}
		case 6:			//6.退费
		{
			Return_Menu();
			break;
		}
		case 7:			//7.查询统计
		{
			Statistic_Menu();
			break;
		}
		case 8:			//8.注销卡
		{
			Delete_Menu();
			break;
		}
		case 0:			//0.退出
		{
			Logout();
			break;
		}
		default:
		{
			cout << "所选不存在！请重新选择！！" << endl;
			continue;
		}
		}

	}
}
