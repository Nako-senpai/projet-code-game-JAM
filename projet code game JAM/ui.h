#ifndef UI_H
#define UI_H
#include <SFML/Graphics.h>
#include "money.h"

#define N_HEARTS 3

typedef struct
{
	int count;
	
}SnowmanIconeID;

typedef struct
{
	int life;
}HP;

void ATH(sfRenderWindow* window);
sfSprite* createSnowmanIcone( sfTexture* texture, float _x, float _y);
void drawMoney(sfRenderWindow* window, Money* money);
void life(sfRenderWindow* window, HP* hp);
#endif