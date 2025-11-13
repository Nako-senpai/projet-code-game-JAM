#include "money.h"

void moneyInit(Money* money, int startAmount)
{
    money->amount = startAmount;
}

void moneyAdd(Money* money, int _x)
{
    money->amount += _x;
}

void moneySpend(Money* money, int _x)
{
    money->amount -= _x;
}

int moneyGet(Money* money)
{
    return money->amount;
}