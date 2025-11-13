#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include "crabe.h"
#include "snowman.h"
#include "grid.h"
#include "snowball.h"
#include "ui.h"
#include "collision.h"
#include "money.h"

typedef struct {
	sfRenderWindow* window;
	Grid grid;
	sfBool mousePressed;
	sfBool snowmanSelected;
	sfSprite* snowmanIconeMouse;
	sfSprite* snowmanIcone;
	sfTexture* snowmanTexture;
}Game;

void initGame(Game* game, Money* money);
void handleEvent(Game* game);
void updateGame(Game* game, Money* money, SnowmanIconeID* iconeID);
void drawGame(Game* game);
void cleanupGame(Game* game);

#endif
