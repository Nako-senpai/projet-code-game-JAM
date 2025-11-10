#include "grid.h"
#include "snowman.h"
#include <stdlib.h>
#include <stdio.h>

void initGrid(Grid* grid, float bordY)
{
	for (int y = 0; y < line; y++) 
	{
		for (int x = 0; x < colum; x++) 
		{
			grid->cells[y][x].occupied = 0;
			grid->cells[y][x].entity = NULL;
			grid->cells[y][x].position = (sfVector2f){ x * caseSize,  y * caseSize - 500 + bordY };
			grid->cells[y][x].posX = x;
			grid->cells[y][x].posY = y;
			grid->cells[y][x].mousePressed = sfFalse;
		}
	}
}

Cell* getIdCase(sfRenderWindow* window, Grid* grid)
{


	sfVector2i mouse = sfMouse_getPositionRenderWindow(window);
	if (mouse.y > 580 && mouse.y < 1200 && mouse.x > 0 && mouse.x < 1000)
	{
		mouse.y -= 580;
		mouse.x /= 100;
		mouse.y /= 100;
		printf("la souris se trouve dans la case %d%d\n", mouse.y, mouse.x);
		return &(grid->cells[mouse.y][mouse.x]);
	}
	return NULL;
}

void drawGrid(sfRenderWindow* window, Grid* grid, sfBool mousePressed) {
	sfRectangleShape* rect = sfRectangleShape_create();
	sfRectangleShape_setSize(rect, (sfVector2f) { caseSize, caseSize });
	sfRectangleShape_setOutlineThickness(rect, 1);
	sfRectangleShape_setOutlineColor(rect, sfBlack);
	Cell* cellUnderMouse = getIdCase(window, grid);

	for (int y = 0; y < line; y++) {
		for (int x = 0; x < colum; x++) {
			sfRectangleShape_setPosition(rect, grid->cells[y][x].position);
			if (cellUnderMouse != NULL && cellUnderMouse->posX == x && cellUnderMouse->posY == y && cellUnderMouse->mousePressed == sfTrue)
			{
				//printf("cette zone marche\n");
			}
			else
				sfRectangleShape_setFillColor(rect, sfTransparent);

			sfRenderWindow_drawRectangleShape(window, rect, NULL);
			mousePressed = sfFalse;
		}
	}
	sfRectangleShape_destroy(rect);
}

void snowmanSpawn(sfRenderWindow* window, Grid* grid, sfBool mousePressed)
{
	Cell* cellUnderMouse = getIdCase(window, grid);

	for (int y = 0; y < line; y++) {
		for (int x = 0; x < colum; x++) {
			if (grid->cells[y][x].occupied == 0 && cellUnderMouse != NULL && cellUnderMouse->posX == x && cellUnderMouse->posY == y && cellUnderMouse->mousePressed == sfTrue)
			{
				newSnowman();
				sfSprite_setPosition(tableauSnowmen[nbSnowmen - 1]->sprite, (sfVector2f) { grid->cells[y][x].position.x, grid->cells[y][x].position.y });
				tableauSnowmen[nbSnowmen - 1]->gridX = x;
				tableauSnowmen[nbSnowmen - 1]->gridY = y;
				printf("cette zone marche\n");
				grid->cells[y][x].occupied = 1;
			}
		}
	}
	mousePressed = sfFalse;
}
