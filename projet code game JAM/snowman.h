#ifndef SNOWMAN_H
#define SNOWMAN_H
#include "grid.h"
#include <SFML/Graphics.h>


typedef struct
{
	sfSprite* sprite;
	sfImage* image;
	int hp;
	sfBool alive;
	int nbSnowman;
	sfClock* clock;
	float cooldown;
	float timer;
	int gridX;
	int gridY;
}Snowman;

extern Snowman** tableauSnowmen;
extern int nbSnowmen;

void freeSnowmen(Grid* grid, int _i);
void newSnowman(void);
sfSprite* createSnowmanIcone(float _x, float _y);
void updateSnowmanAttack(Snowman* snowmanID);
void snowmanHurt(Grid* grid);
#endif