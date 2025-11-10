#include "ui.h"
#include <stdlib.h>
#include <stdio.h>

void ATH(sfRenderWindow* window)
{
	sfRectangleShape* ATH = sfRectangleShape_create();
	sfRectangleShape_setSize(ATH, (sfVector2f) { 100, 1200 });
	sfRectangleShape_setFillColor(ATH, sfGreen);
	sfRectangleShape_setPosition(ATH, (sfVector2f) { 1000, 0 });
	sfRenderWindow_drawRectangleShape(window, ATH, NULL);
}

sfSprite* createSnowmanIcone(float _x, float _y)
{
	sfTexture* snowman_texture = sfTexture_createFromFile("assets/Sprites/snowmen.png", NULL);
	sfSprite* snowman = sfSprite_create();
	sfSprite_setTexture(snowman, snowman_texture, sfTrue);
	sfSprite_setPosition(snowman, (sfVector2f) { _x, _y });
	return snowman;
}