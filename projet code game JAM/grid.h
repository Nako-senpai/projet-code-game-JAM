#ifndef GRID_H
#define GRID_H
#include <SFML/Graphics.h>

#define colum 10
#define line 5
#define caseSize 100

typedef struct {
	int posX;
	int posY;
	sfBool occupied; // case occupé??
	void* entity; // struct pour une entité
	sfVector2f position; // position en pixels
	sfBool mousePressed;
}Cell;

//struct pour les dimension
typedef struct {
	Cell cells[line][colum];
}Grid;

void initGrid(Grid* grid, float bordY);
Cell* getIdCase(sfRenderWindow* window, Grid* grid);
void drawGrid(sfRenderWindow* window, Grid* grid, sfBool mousePressed);
void snowmanSpawn(sfRenderWindow* window, Grid* grid, sfBool mousePressed);

#endif
