//#include<string.h>
//#include<stdlib.h>
//#include"struct.h"
//#include"global.h"
//#include "cardservice.h"
//#include<iostream>
//
//Card aCard[50];	//����Ϣ�ṹ������
//int nCount = 0;	//����Ϣʵ�ʸ���
//lpCardNode cardList = NULL;
//
////��ʼ������
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
////�ͷŽ��ռ�
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
//		//�������
//		while (p->next != NULL)
//		{
//			if (strcmp(p->data.aName, card.aName) == 0)
//			{
//				std::cout << "�����Ѵ��ڣ���" << "\n";
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
////�жϿ��Ƿ����
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