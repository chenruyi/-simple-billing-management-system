#ifndef MODEL_H
#define MODEL_H

#include<time.h>
#include"global.h"

typedef struct Card
{
	char aName[18];	//卡号
	char aPwd[8];	//密码

	int nStatus;	//卡状态（0-未上机；1-正在上机；2-已注销；3-失效）
	float fAmount;	//累计金额
	int nUseCount;	//使用次数
	float fBalance;	//余额
	int nDel;		//删除标志（0-未删除；1-删除）

	time_t tStart;	//开卡时间
	time_t tEnd;	//截至时间
	time_t tLast;	//最后使用时间

}Card;

typedef struct CardNode
{
	Card data;
	struct CardNode *next;

}CardNode, *lpCardNode;

typedef struct usingInfo
{
	char aName[18];	//卡号
	int nStatus;	//卡状态（0-未上机；1-正在上机；2-已注销；3-失效）
	time_t operate_time;//操作时间card->start;
	float fBalance;	//余额

}usingInfo;

#endif


