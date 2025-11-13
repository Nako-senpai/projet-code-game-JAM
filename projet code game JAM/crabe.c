#include "crabe.h"
#include "snowball.h"
#include "snowman.h"
#include <stdlib.h>
#include <stdio.h>

Crabe** tableauCrabe = NULL;
int nbCrabe=0;

float randomeLinesSpawn()
{
	float randomLine = 0;

	randomLine = (((rand() % 10) + 1) * 100) - 50;
	return randomLine;
}

void freeCrabe(int _i)
{
	if (tableauCrabe[_i] == NULL)
		return;

	sfSprite_destroy(tableauCrabe[_i]->sprite);
	free(tableauCrabe[_i]);

	if (_i < nbCrabe - 1)
		tableauCrabe[_i] = tableauCrabe[nbCrabe - 1];

	tableauCrabe[nbCrabe - 1] = NULL;
	nbCrabe--;
}

void newCrabe()
{
	sfTexture* crabe_texture = sfTexture_createFromFile("assets/Sprites/crabe.png", NULL);
	if (!crabe_texture)
	{
		printf("Erreur: impossible de charger crabe.png\n");
		exit(1);
	}
	Crabe* newCrabe = malloc(sizeof(Crabe));
	newCrabe->sprite = sfSprite_create();
	sfSprite_setTexture(newCrabe->sprite, crabe_texture, sfTrue);
	newCrabe->image = sfTexture_copyToImage(crabe_texture);
	sfSprite_setPosition(newCrabe->sprite, (sfVector2f) { randomeLinesSpawn(), -50 });
	sfVector2u size = sfTexture_getSize(crabe_texture);
	sfSprite_setOrigin(newCrabe->sprite, (sfVector2f) { size.x / 2.0f, size.y / 2.0f });
	newCrabe->hp = 100;
	newCrabe->damage = 50;
	newCrabe->alive = sfTrue;
	newCrabe->active = sfTrue;
	newCrabe->velocity = (sfVector2f){ 0.0f,0.5f };
	newCrabe->position = sfSprite_getPosition(newCrabe->sprite);

	newCrabe->clock = sfClock_create();
	newCrabe->cooldown = 1000.0f;
	newCrabe->timer = 0.0f;

	newCrabe->attakClock = sfClock_create();
	newCrabe->attakCooldown = 2.0f;
	newCrabe->attakTimer = 0.0f;

	nbCrabe++;
	tableauCrabe = realloc(tableauCrabe, nbCrabe * sizeof(Crabe*));
	tableauCrabe[nbCrabe - 1] = newCrabe;
}

void updateCrabeMouvement()
{
	for (int i = 0; i < nbCrabe; i++)
	{
		if (tableauCrabe[i]->active)
		{
			tableauCrabe[i]->position.y += tableauCrabe[i]->velocity.y;
			sfSprite_setPosition(tableauCrabe[i]->sprite, tableauCrabe[i]->position);

			if (tableauCrabe[i]->position.y > 1200)
			{
				freeCrabe(i);
				i--;
			}
		}
	}
}

void spawnCrabe(Crabe* crabeID)
{
	sfTime elapsed = sfClock_getElapsedTime(crabeID->clock);
	float delta = sfTime_asSeconds(elapsed);
	crabeID->timer += delta;
	if (crabeID->timer >= crabeID->cooldown)
	{
		//ici mon attak
		newCrabe();
		printf("crabe attak\n");
		crabeID->timer = 0;
		sfClock_restart(crabeID->clock);
	}
}

void crabeHurt()
{
	for (int i = 0; i < nbCrabe; i++)
	{
		for (int j = 0; j < nbSnowball; j++)
		{
			if (!tableauCrabe[i]->active)
				continue;
			if (!tableauSnowball[j]->active)
				continue;
			if (pixelPerfectCollision(tableauSnowball[j]->sprite, tableauSnowball[j]->image, tableauCrabe[i]->sprite, tableauCrabe[i]->image))
			{

				tableauCrabe[i]->hp -= tableauSnowball[j]->damage;
				tableauSnowball[j]->active = sfFalse;
				if (tableauCrabe[i]->hp <= 0)
				{
					tableauCrabe[i]->alive = sfFalse;
				}
			}

		}
	}
	for (int i = 0; i < nbCrabe; i++) {
		if (tableauCrabe[i] != NULL && tableauCrabe[i]->alive == sfFalse) {
			freeCrabe(i);
			i--;
		}
	}

	for (int i = 0; i < nbSnowball; i++) {
		if (tableauSnowball[i] != NULL && tableauSnowball[i]->active == sfFalse) {
			freeSnowball(i);
			i--;
		}
	}
}

void crabeAttak(int _i, int _j)
{
	tableauSnowmen[_j]->hp -= tableauCrabe[_i]->damage;
	sfSprite_setColor(tableauSnowmen[_j], (sfColor) { 255, 0, 0, 0 });
}