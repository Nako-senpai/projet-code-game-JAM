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

typedef struct {
	sfRenderWindow* window;
	Grid grid;
	sfBool mousePressed;
	sfBool snowmanSelected;
	sfSprite* snowmanIconeMouse;
}Game;

void initGame(Game* game);
void handleEvents(Game* game);
void updateGame(Game* game);
void drawGame(Game* game);
void cleanupGame(Game* game);

#endif
