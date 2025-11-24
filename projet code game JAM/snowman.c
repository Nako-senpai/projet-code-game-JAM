#include "snowman.h"
#include "snowball.h"
#include "crabe.h"
#include "grid.h"
#include <stdlib.h>
#include <stdio.h>

Snowman** tableauSnowmen = NULL;
int nbSnowmen = 0;

void freeSnowmen(Grid * grid, int _i)
{
	if (tableauSnowmen[_i] == NULL)
		return;

	int x = tableauSnowmen[_i]->gridX;
	int y = tableauSnowmen[_i]->gridY;
	grid->cells[y][x].occupied = 0;

	sfSprite_destroy(tableauSnowmen[_i]->sprite);
	free(tableauSnowmen[_i]);

	if (_i < nbSnowmen - 1)
		tableauSnowmen[_i] = tableauSnowmen[nbSnowmen - 1];

	tableauSnowmen[nbSnowmen - 1] = NULL;
	nbSnowmen--;
}

void newSnowman()
{
	sfTexture* snowman_texture = sfTexture_createFromFile("assets/Sprites/snowmen.png", NULL);
	Snowman* newSnowman = malloc(sizeof(Snowman));
	newSnowman->sprite = sfSprite_create();
	sfSprite_setTexture(newSnowman->sprite, snowman_texture, sfTrue);
	newSnowman->image = sfTexture_copyToImage(snowman_texture);
	sfSprite_setOrigin(newSnowman->sprite, (sfVector2f) { 0, 0 });
	sfSprite_setScale(newSnowman->sprite, (sfVector2f) { 3, 3 });
	newSnowman->hp = 100;
	newSnowman->alive = sfTrue;

	newSnowman->clock = sfClock_create();
	newSnowman->cooldown = 100.0f;
	newSnowman->timer = 0.0f;

	//le cost n'est pas associé au snwoman créé mais au snowmanIcone


	nbSnowmen++;
	tableauSnowmen = realloc(tableauSnowmen, nbSnowmen * sizeof(Snowman*));
	tableauSnowmen[nbSnowmen - 1] = newSnowman;
}

void updateSnowmanAttack(Snowman* snowmanID)
{
	if (!snowmanID->alive) return;


	sfTime elapsed = sfClock_getElapsedTime(snowmanID->clock);
	float delta = sfTime_asSeconds(elapsed);

	snowmanID->timer += delta;
	if (snowmanID->timer >= snowmanID->cooldown)
	{
		//ici mon attak
		SnowmanAttack(snowmanID);
		printf("snowman attak\n");
		snowmanID->timer = 0;
		sfClock_restart(snowmanID->clock);
	}
}

void snowmanHurt(Grid* grid)
{

	for (int i = 0; i < nbCrabe; i++)
	{
		for (int j = 0; j < nbSnowmen; j++)
		{
			if (!tableauCrabe[i]->active)
				continue;
			if (!tableauSnowmen[j]->alive)
				continue;
			if (pixelPerfectCollision(tableauSnowmen[j]->sprite, tableauSnowmen[j]->image, tableauCrabe[i]->sprite, tableauCrabe[i]->image))
			{
				sfTime elapsed = sfClock_getElapsedTime(tableauCrabe[i]->attakClock);
				float delta = sfTime_asSeconds(elapsed);

				tableauCrabe[i]->attakTimer += delta;
				sfClock_restart(tableauCrabe[i]->attakClock);

				tableauCrabe[i]->velocity = (sfVector2f){ 0.0f,0.0f };

				if (tableauCrabe[i]->attakTimer >= tableauCrabe[i]->attakCooldown)
				{
					crabeAttak(i, j);
					printf("collision!\n");
					tableauCrabe[i]->attakTimer = 0;
					sfClock_restart(tableauCrabe[i]->attakClock);

				}
				if (tableauSnowmen[j]->hp <= 0)
				{
					tableauSnowmen[j]->alive = sfFalse;
					tableauCrabe[i]->velocity = (sfVector2f){ 0.0f,0.5f };
				}
			}

		}
	}
	for (int i = 0; i < nbSnowmen; i++)
	{
		if (tableauSnowmen[i] != NULL && tableauSnowmen[i]->alive == sfFalse)
		{
			freeSnowmen(grid, i);
			i--;
		}
	}

}