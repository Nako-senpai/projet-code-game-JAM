#ifndef MONEY_H
#define MONEY_H

typedef struct
{
	int amount;
}Money;


void moneyInit(Money* money, int _x);
void moneyAdd(Money* money, int _x);
void moneySpend(Money* money, int _x);
int moneyGet(Money* money);
#endif

