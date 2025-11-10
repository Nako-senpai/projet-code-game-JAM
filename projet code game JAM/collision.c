#include "collision.h"
#include <stdlib.h>
#include <stdio.h>

sfBool pixelPerfectCollision(sfSprite* s1, sfImage* img1, sfSprite* s2, sfImage* img2)
{
	sfFloatRect rect1 = sfSprite_getGlobalBounds(s1);
	sfFloatRect rect2 = sfSprite_getGlobalBounds(s2);

	sfFloatRect intersect;
	if (!sfFloatRect_intersects(&rect1, &rect2, &intersect))
		return sfFalse;

	sfVector2u size1 = sfImage_getSize(img1);
	sfVector2u size2 = sfImage_getSize(img2);

	for (int x = intersect.left; x < intersect.left + intersect.width; x++)
	{
		for (int y = intersect.top; y < intersect.top + intersect.height; y++)
		{
			sfVector2f point = { (float)x, (float)y };
			sfTransform inverseP1 = sfSprite_getInverseTransform(s1);
			sfVector2f p1 = sfTransform_transformPoint(&inverseP1, point);
			sfTransform inverseP2 = sfSprite_getInverseTransform(s2);
			sfVector2f p2 = sfTransform_transformPoint(&inverseP2, point);

			if (p1.x < 0 || p1.y < 0 || p2.x < 0 || p2.y < 0 ||
				p1.x >= size1.x || p1.y >= size1.y || p2.x >= size2.x || p2.y >= size2.y)
				continue;
			sfColor c1 = sfImage_getPixel(img1, (unsigned)p1.x, (unsigned)p1.y);
			sfColor c2 = sfImage_getPixel(img2, (unsigned)p2.x, (unsigned)p2.y);

			if (c1.a > 0 && c2.a > 0)
				return sfTrue;
		}
	}
	return sfFalse;
}
