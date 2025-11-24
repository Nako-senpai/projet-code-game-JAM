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
	sfSprite_setScale(snowman, (sfVector2f) { 3, 3 });

	return snowman;
	
}

void life(sfRenderWindow* window, HP* hp)
{
	
	sfSprite* nbHeart[N_HEARTS];
	sfTexture* heart = sfTexture_createFromFile("assets/Sprites/heart.png", NULL);
	for (int i = 0; i < N_HEARTS; i++)
	{
		nbHeart[i] = sfSprite_create();
		sfSprite_setTexture(nbHeart[i], heart, sfTrue);
		sfSprite_setPosition(nbHeart[i], (sfVector2f) { 985, 300 + (90 * i) });
		sfSprite_setScale(nbHeart[i], (sfVector2f) { 0.5f, 0.5f });
	}

	for (int i = 2; i >= hp->life; --i)
		sfSprite_setColor(nbHeart[i], sfBlack);

	for (int i = 0; i < N_HEARTS; ++i)
		sfRenderWindow_drawSprite(window, nbHeart[i], NULL);

	

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