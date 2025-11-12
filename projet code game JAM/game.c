#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initGame(Game* game)
{
	srand(time(NULL));
	float bordX = 1100;
	float bordY = 1080;
	sfVideoMode videoMode = { bordX, bordY, 32 };
	game->window = sfRenderWindow_create(videoMode, "sprite", sfDefaultStyle, NULL);
	game->mousePressed = sfFalse;
	game->snowmanSelected = sfFalse;
	game->snowmanIconeMouse = NULL;

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

void updateGame(Game* game)
{
	sfSprite* snowmanIcone = createSnowmanIcone(1000, 10);
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
			printf("%d %d %d\n", pixelColor.r, pixelColor.g, pixelColor.b);
			printf("cette zone marche\n");
			printf("cette zone marche aussi\n");
			if (game->mousePressed)
			{
				game->snowmanSelected = sfTrue;
				printf("cette zone marche\n");
			}
			game->mousePressed = sfFalse;
		}
	}
	if (game->snowmanSelected)
	{
		game->snowmanIconeMouse = createSnowmanIcone((float)mouse.x, (float)mouse.y);
		if (game->mousePressed)
		{
			snowmanSpawn(game->window, &game->grid, game->mousePressed);
			game->snowmanSelected = sfFalse;
			sfSprite_setPosition(game->snowmanIconeMouse, (sfVector2f) { -100, -100 });
		}
	}
	for (int i = 0; i < nbSnowmen; i++)
	{
		updateSnowmanAttack(tableauSnowmen[i]);
	}

	if (nbCrabe > 0) {
		spawnCrabe(tableauCrabe[0]);
	}


	crabeHurt();
	snowmanHurt(&game->grid);
	updateCrabeMouvement();
	updateSnowball();


	game->mousePressed = sfFalse;
}

void drawGame(Game* game)
{
	sfRenderWindow_clear(game->window, sfBlue);
	ATH(game->window);

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
	sfRenderWindow_destroy(game->window);
}