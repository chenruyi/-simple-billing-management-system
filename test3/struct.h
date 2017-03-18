#ifndef MODEL_H
#define MODEL_H

#include<time.h>
#include"global.h"

typedef struct Card
{
	char aName[18];	//����
	char aPwd[8];	//����

	int nStatus;	//��״̬��0-δ�ϻ���1-�����ϻ���2-��ע����3-ʧЧ��
	float fAmount;	//�ۼƽ��
	int nUseCount;	//ʹ�ô���
	float fBalance;	//���
	int nDel;		//ɾ����־��0-δɾ����1-ɾ����

	time_t tStart;	//����ʱ��
	time_t tEnd;	//����ʱ��
	time_t tLast;	//���ʹ��ʱ��

}Card;

typedef struct CardNode
{
	Card data;
	struct CardNode *next;

}CardNode, *lpCardNode;

typedef struct usingInfo
{
	char aName[18];	//����
	int nStatus;	//��״̬��0-δ�ϻ���1-�����ϻ���2-��ע����3-ʧЧ��
	time_t operate_time;//����ʱ��card->start;
	float fBalance;	//���

}usingInfo;

#endif


