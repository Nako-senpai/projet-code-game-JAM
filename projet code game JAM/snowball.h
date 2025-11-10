#ifndef SNOWBALL_H
#define SNOWBALL_H
#include <SFML/Graphics.h>
#include "snowman.h"
typedef struct
{
	sfSprite* sprite;
	sfImage* image;
	sfVector2f position;
	sfVector2f velocity;
	sfBool active;//pour la sorti
	int damage;
}Snowball;


extern Snowball** tableauSnowball;
extern int nbSnowball;

void freeSnowball(int _i);
void SnowmanAttack(Snowman* snowmanID);
void updateSnowball();
#endif