#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <process.h>

#include "crabe.h"
#include "snowman.h"
#include "grid.h"
#include "snowball.h"
#include "ui.h"
#include "collision.h"


int main(void)
{

	float bordX = 1100;
	float bordY = 1080;
	srand(time(NULL));

	sfBool mousePressed = sfFalse;
	sfBool mousePressedAgain = sfFalse;
	sfBool snowmanSelected = sfFalse;
	sfSprite* snowmanIconeMouse = NULL;




	sfVideoMode videoMode = { bordX, bordY, 32 };
	sfRenderWindow* window = sfRenderWindow_create(videoMode, "sprite", sfDefaultStyle, NULL);



	newCrabe();
	sfEvent event;

	while (sfRenderWindow_isOpen(window))
	{
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed)
				sfRenderWindow_close(window);
			if (event.type == sfEvtMouseButtonPressed)
			{
				Cell* idCell = getIdCase(window, &grid);
				if (idCell != NULL)
				{
					idCell->mousePressed = sfTrue;
				}

				mousePressed = sfTrue;
			}
		}

		// utiliser pour l'interaction de la sourie (et + plus tard)
		Cell* idCell = getIdCase(window, &grid);


		sfSprite* snowmanIcone = createSnowmanIcone(1000, 10);
		sfVector2i mouse = sfMouse_getPositionRenderWindow(window);
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
				if (mousePressed)
				{
					snowmanSelected = sfTrue;
					printf("cette zone marche\n");
				}
				mousePressed = sfFalse;
			}
		}
		if (snowmanSelected)
		{
			snowmanIconeMouse = createSnowmanIcone((float)mouse.x, (float)mouse.y);
			if (mousePressed)
			{
				snowmanSpawn(window, &grid, mousePressed);
				snowmanSelected = sfFalse;
				sfSprite_setPosition(snowmanIconeMouse, (sfVector2f) { -100, -100 });
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
		snowmanHurt();


		//idCell->mousePressed = sfFalse;
		mousePressed = sfFalse;
		sfRenderWindow_clear(window, sfBlue);
		ATH(window);
		updateCrabeMouvement();
		updateSnowball();
		sfRenderWindow_drawSprite(window, snowmanIcone, NULL);

		if (snowmanIconeMouse != NULL)
			sfRenderWindow_drawSprite(window, snowmanIconeMouse, NULL);

		for (int i = 0; i < nbSnowmen; i++)
		{
			if (tableauSnowmen[i]->alive)
			{
				sfRenderWindow_drawSprite(window, tableauSnowmen[i]->sprite, NULL);
			}
		}

		for (int i = 0; i < nbSnowball; i++)
		{
			if (tableauSnowball[i]->active)
				sfRenderWindow_drawSprite(window, tableauSnowball[i]->sprite, NULL);
		}

		for (int i = 0; i < nbCrabe; i++)
		{
			if (tableauCrabe[i]->active)
				sfRenderWindow_drawSprite(window, tableauCrabe[i]->sprite, NULL);
		}

		drawGrid(window, &grid, mousePressed);
		sfRenderWindow_display(window);

	}

	// Libération des ressources

	sfRenderWindow_destroy(window);

	return EXIT_SUCCESS;
}