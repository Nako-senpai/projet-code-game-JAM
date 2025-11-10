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

		// utiliser pour l'interaction de la sourie (et + plus tard)
		Cell* idCell = getIdCase(window, &grid);



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