#ifndef MODEL_H
#define MODEL_H

#include<time.h>
#include"global.h"

typedef struct Card
{
	char aName[NAME_MAX];	//����
	char aPwd[PSD_MAX];	//����

	int nStatus;	//��״̬��0-δ�ϻ���1-�����ϻ���2-��ע����3-ʧЧ��
	float fAmount;	//�ۼƽ��
	int nUseCount;	//ʹ�ô���
	float fBalance;	//���
	int nDel;		//ɾ����־��0-δɾ����1-ɾ����

	time_t tStart;	//����ʱ��
	time_t tEnd;	//����ʱ��,ע������ʱ��
	time_t tLast;	//���ʹ��ʱ��

}Card;

typedef struct CardNode
{
	Card data;
	struct CardNode *next;

}CardNode, *lpCardNode;

enum {O_addcard,O_login,O_logout,O_deposit,O_return,O_delete};
typedef struct usingInfo
{
	char aName[18];	//����
	int operatekind;	//������0-���ӿ���1-�ϻ���2-�»���3-��ֵ��4-�˷ѣ�5-ע������
	time_t operate_time;//����ʱ��card->start;
	float fBalance;	//���

}usingInfo;

#endif


