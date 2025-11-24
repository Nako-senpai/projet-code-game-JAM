#include "snowball.h"
#include <stdlib.h>
#include <stdio.h>

Snowball** tableauSnowball = NULL;
int nbSnowball = 0;

void freeSnowball(int _i)
{
	if (tableauSnowball[_i] == NULL)
		return;

	sfSprite_destroy(tableauSnowball[_i]->sprite);
	free(tableauSnowball[_i]);

	if (_i < nbSnowball - 1)
		tableauSnowball[_i] = tableauSnowball[nbSnowball - 1];

	tableauSnowball[nbSnowball - 1] = NULL;
	nbSnowball--;
}

void SnowmanAttack(Snowman* snowmanID)
{
	sfTexture* snowballtexture = sfTexture_createFromFile("assets/Sprites/snowball.png", NULL);
	Snowball* newSnowball = malloc(sizeof(Snowball));
	newSnowball->sprite = sfSprite_create();
	sfSprite_setTexture(newSnowball->sprite, snowballtexture, sfTrue);
	newSnowball->image = sfTexture_copyToImage(snowballtexture);
	sfSprite_setOrigin(newSnowball->sprite, (sfVector2f) { 0, 0 });
	sfSprite_setScale(newSnowball->sprite, (sfVector2f) { 2, -2 });
	newSnowball->position = sfSprite_getPosition(snowmanID->sprite);
	sfSprite_setPosition(newSnowball->sprite, newSnowball->position);
	newSnowball->velocity = (sfVector2f){ 0.0f,3.0f };
	newSnowball->active = sfTrue;
	newSnowball->damage = 10;
	nbSnowball++;
	tableauSnowball = realloc(tableauSnowball, nbSnowball * sizeof(Snowball*));

	tableauSnowball[nbSnowball - 1] = newSnowball;
}

void updateSnowball()
{
	for (int i = 0; i < nbSnowball; i++)
	{
		if (tableauSnowball[i]->active)
		{
			tableauSnowball[i]->position.y -= tableauSnowball[i]->velocity.y;
			sfSprite_setPosition(tableauSnowball[i]->sprite, tableauSnowball[i]->position);

			if (tableauSnowball[i]->position.y < 0)
			{
				freeSnowball(i);
				i--;
			}
		}
	}
}

