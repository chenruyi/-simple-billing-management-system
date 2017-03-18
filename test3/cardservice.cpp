//#include<string.h>
//#include<stdlib.h>
//#include"struct.h"
//#include"global.h"
//#include "cardservice.h"
//#include<iostream>
//
//Card aCard[50];	//卡信息结构体数组
//int nCount = 0;	//卡信息实际个数
//lpCardNode cardList = NULL;
//
////初始化链表
//bool initCardList(lpCardNode &card_head)
//{
//	bool flag = false;
//	card_head = (lpCardNode)malloc(sizeof(CardNode));
//	if (card_head != NULL)
//	{
//		card_head->next = NULL;
//		flag = true;
//
//	}
//	return flag;
//}
////释放结点空间
//void freeNode(lpCardNode Node) {
//	free(Node);
//}
//
//
//
//
//bool AddCard(Card card)
//{
//	lpCardNode cur = NULL;
//	lpCardNode p = cardList;
//	if (p == NULL)
//		if (!initCardList(p))
//		{
//			return false;
//		}
//	cur = (lpCardNode)malloc(sizeof(CardNode));
//	if (cur != NULL)
//	{
//		cur->data = card;
//		cur->next = NULL;
//		//遍历结点
//		while (p->next != NULL)
//		{
//			if (strcmp(p->data.aName, card.aName) == 0)
//			{
//				std::cout << "卡号已存在！！" << "\n";
//			}
//			p = p->next;
//		}
//		p->next = cur;
//		cardList = p;
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
//bool DeleteCard(char * aName)
//{
//	lpCardNode p = cardList;
//	bool flag = false;
//	while (p->next)
//	{
//		if (strcmp(p->next->data.aName, aName) == 0)
//		{
//			p = p->next->next;
//			flag = true;
//			freeNode(p->next);
//		}
//		p = p->next;
//	}
//	return false;
//}
//
////判断卡是否存在
//Card* SelectCard(char *cardname) {
//	lpCardNode p = cardList;
//	Card *card = NULL;
//	while (p)
//	{
//		if (strcmp(p->data.aName, cardname) == 0)
//		{
//			card = &(p->data);
//			break;
//		}
//		p = p->next;
//	}
//
//	return card;
//}