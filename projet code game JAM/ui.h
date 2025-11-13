#ifndef UI_H
#define UI_H
#include <SFML/Graphics.h>

typedef struct
{
	int count;
}SnowmanIconeID;

void ATH(sfRenderWindow* window);
sfSprite* createSnowmanIcone(SnowmanIconeID* iconeID, float _x, float _y);
#endif