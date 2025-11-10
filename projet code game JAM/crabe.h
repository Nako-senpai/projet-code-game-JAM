#ifndef CRABE_H
#define CRABE_H
#include <SFML/Graphics.h>


typedef struct
{
	sfSprite* sprite;
	sfImage* image;
	int hp;
	int damage;
	sfBool alive;
	int nbCrabe;
	sfVector2f position;
	sfVector2f velocity;
	sfBool active;
	sfClock* clock;
	float cooldown;
	float timer;
	sfClock* attakClock;
	float attakCooldown;
	float attakTimer;
}Crabe;


extern Crabe** tableauCrabe;
extern int nbCrabe;

void newCrabe(void);
void freeCrabe(int _i);
void updateCrabeMouvement(void);
void spawnCrabe(Crabe* crabeID);
void crabeHurt();
void crabeAttak(int _i, int _j);
#endif // !CRABE_H