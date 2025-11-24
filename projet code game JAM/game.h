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

typedef enum
{
	MENUE,
	PLAYING,
	PAUSE,
	GAME_OVER,
}GameState;

typedef struct {
	sfRenderWindow* window;
	Grid grid;
	sfBool mousePressed;
	sfBool snowmanSelected;
	sfSprite* snowmanIconeMouse;
	sfSprite* snowmanIcone;
	sfTexture* snowmanTexture;
	GameState state;

	sfSprite* backScreen;
	sfTexture* fond;

	int life;
}Game;



void initGame(Game* game, Money* money, SnowmanIconeID* iconeID, HP* hp);
void handleEvent(Game* game);
void updateGame(Game* game, Money* money, SnowmanIconeID* iconeID, HP* hp);
void drawGame(Game* game, Money* money, HP* hp);
void updateMenu(Game* game);
void drawMenu(Game* game);
void cleanupGame(Game* game);
void life(sfRenderWindow* window, HP* hp);
#endif
