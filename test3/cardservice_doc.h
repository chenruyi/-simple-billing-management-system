#ifndef CARD_SERVICE_H
#define CARD_SERVICE_H 

bool AddCard(Card card);//增加卡
bool DeleteCard(Card card_delete);//注销卡
Card* SelectCard(char *cardname);//查询卡，返回卡信息
#endif
