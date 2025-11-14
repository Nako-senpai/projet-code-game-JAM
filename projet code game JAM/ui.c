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
	sfRectangleShape_destroy(ATH);
}

sfSprite* createSnowmanIcone(sfTexture* texture, float _x, float _y)
{	
	sfSprite* snowman = sfSprite_create();
	sfSprite_setTexture(snowman, texture, sfFalse);
	sfSprite_setPosition(snowman, (sfVector2f) { _x, _y });

	return snowman;
	
}

void drawMoney(sfRenderWindow* window, Money* money)
{
	static sfFont* font = NULL;
	static sfText* text = NULL;

	if (font == NULL)
	{
		font = sfFont_createFromFile("assets/Font/arial.ttf");
		if (!font)
		{
			printf("erreur chargement police");
			return;
		}
		text = sfText_create();
		sfText_setFont(text, font);
		sfText_setCharacterSize(text, 28);
		sfText_setFillColor(text, sfBlack);
		sfText_setPosition(text, (sfVector2f) { 1010, 60 });
	}
	char buffer[64];
	sprintf_s(buffer, sizeof(buffer), "$ %d", moneyGet(money));
	//printf("%d\n", moneyGet(money));
	sfText_setString(text, buffer);

	sfRenderWindow_drawText(window, text, NULL);

}