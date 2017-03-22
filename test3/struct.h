#ifndef MODEL_H
#define MODEL_H

#include<time.h>
#include"global.h"

typedef struct Card
{
	char aName[NAME_MAX];	//卡号
	char aPwd[PSD_MAX];	//密码

	int nStatus;	//卡状态（0-未上机；1-正在上机；2-已注销；3-失效）
	float fAmount;	//累计金额
	int nUseCount;	//使用次数
	float fBalance;	//余额
	int nDel;		//删除标志（0-未删除；1-删除）

	time_t tStart;	//开卡时间
	time_t tEnd;	//截至时间,注销卡的时间
	time_t tLast;	//最后使用时间

}Card;

typedef struct CardNode
{
	Card data;
	struct CardNode *next;

}CardNode, *lpCardNode;

enum {O_addcard,O_login,O_logout,O_deposit,O_return,O_delete};
typedef struct usingInfo
{
	char aName[18];	//卡号
	int operatekind;	//操作（0-增加卡；1-上机；2-下机；3-充值；4-退费；5-注销卡）
	time_t operate_time;//操作时间card->start;
	float fBalance;	//余额

}usingInfo;

#endif


