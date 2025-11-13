#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initGame(Game* game, Money* money)
{
	srand(time(NULL));
	float bordX = 1100;
	float bordY = 1080;
	sfVideoMode videoMode = { bordX, bordY, 32 };
	game->window = sfRenderWindow_create(videoMode, "sprite", sfDefaultStyle, NULL);
	game->mousePressed = sfFalse;
	game->snowmanSelected = sfFalse;
	game->snowmanIconeMouse = NULL;

	game->snowmanTexture = sfTexture_createFromFile("assets/Sprites/Snowmen.png", NULL);
	game->snowmanIcone = sfSprite_create();
	sfSprite_setTexture(game->snowmanIcone, game->snowmanTexture, sfTrue);
	sfSprite_setPosition(game->snowmanIcone, (sfVector2f) { 1000, 110 });

	moneyInit(money, 100);
	printf("%d", moneyGet(money));

	initGrid(&game->grid, bordY);
	newCrabe();
}

void handleEvent(Game* game)
{
	sfEvent event;

	while (sfRenderWindow_pollEvent(game->window, &event))
	{
		if (event.type == sfEvtClosed)
			sfRenderWindow_close(game->window);
		if (event.type == sfEvtMouseButtonPressed)
		{
			Cell* idCell = getIdCase(game->window, &game->grid);
			if (idCell != NULL)
			{
				idCell->mousePressed = sfTrue;
			}

			game->mousePressed = sfTrue;
		}
	}
}

void updateGame(Game* game, Money* money, SnowmanIconeID* iconeID)
{

	sfSprite* snowmanIcone = createSnowmanIcone(iconeID, 1000, 110);
	sfVector2i mouse = sfMouse_getPositionRenderWindow(game->window);
	sfFloatRect snowman_bounds = sfSprite_getGlobalBounds(snowmanIcone);

	if (sfFloatRect_contains(&snowman_bounds, (float)mouse.x, (float)mouse.y))
	{
		sfTexture* snowmanTexture = sfSprite_getTexture(snowmanIcone);
		sfImage* snowmanImage = sfTexture_copyToImage(snowmanTexture);
		sfVector2u pixelPos = { mouse.x - snowman_bounds.left ,mouse.y - snowman_bounds.top };
		sfColor pixelColor = sfImage_getPixel(snowmanImage, pixelPos.x, pixelPos.y);

		if (pixelColor.a != 0)
		{
			if (game->mousePressed)
			{
				printf("%d  ", iconeID->count);
				printf("%d\n", money->amount);
				if (money->amount >= iconeID->count)
				{
					game->snowmanSelected = sfTrue;
					printf("cette zone marche\n");
				}
				else
				{
					printf("quantité insuffisante\n");
				}
			}
			game->mousePressed = sfFalse;
		}
	}
	if (game->snowmanSelected)
	{
		game->snowmanIconeMouse = createSnowmanIcone(iconeID, (float)mouse.x, (float)mouse.y);
		if (game->mousePressed)
		{
			{
				Cell* cell = getIdCase(game->window, &game->grid);
				if (cell != NULL && !cell->occupied)
				{
					snowmanSpawn(game->window, &game->grid, game->mousePressed);
					moneySpend(money, iconeID->count);
					printf("%d", moneyGet(money));

				}
				game->snowmanSelected = sfFalse;
				sfSprite_setPosition(game->snowmanIconeMouse, (sfVector2f) { -100, -100 });

			}
		}
	}
	for (int i = 0; i < nbSnowmen; i++)
	{
		updateSnowmanAttack(tableauSnowmen[i]);
	}

	if (nbCrabe > 0) {
		spawnCrabe(tableauCrabe[0]);
	}


	crabeHurt(money);
	snowmanHurt(&game->grid);
	updateCrabeMouvement();
	updateSnowball();


	game->mousePressed = sfFalse;
}

void drawGame(Game* game, Money* money)
{
	sfRenderWindow_clear(game->window, sfBlue);
	ATH(game->window);

	drawMoney(game->window, money);
	sfRenderWindow_drawSprite(game->window, game->snowmanIcone, NULL);
	if (game->snowmanIconeMouse != NULL)
		sfRenderWindow_drawSprite(game->window, game->snowmanIconeMouse, NULL);

	for (int i = 0; i < nbSnowmen; i++)
	{
		if (tableauSnowmen[i]->alive)
		{
			sfRenderWindow_drawSprite(game->window, tableauSnowmen[i]->sprite, NULL);
		}
	}

	for (int i = 0; i < nbSnowball; i++)
	{
		if (tableauSnowball[i]->active)
			sfRenderWindow_drawSprite(game->window, tableauSnowball[i]->sprite, NULL);
	}

	for (int i = 0; i < nbCrabe; i++)
	{
		if (tableauCrabe[i]->active)
			sfRenderWindow_drawSprite(game->window, tableauCrabe[i]->sprite, NULL);
	}

	drawGrid(game->window, &game->grid, game->mousePressed);
	sfRenderWindow_display(game->window);
}

void cleanupGame(Game* game)
{
	if (game->snowmanIcone)
		sfSprite_destroy(game->snowmanIcone);
	if (game->snowmanIconeMouse)
		sfSprite_destroy(game->snowmanIconeMouse);
	if (game->snowmanTexture)
		sfTexture_destroy(game->snowmanTexture);

	sfRenderWindow_destroy(game->window);
}