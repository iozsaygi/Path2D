#include "Physics.h"

bool IsPositionInsideRectangle(float x, float y, SDL_Rect* rect)
{
	if (x >= rect->x && x < (rect->x + rect->w))
	{
		if (y >= rect->y && y < (rect->y + rect->h))
			return true;
	}

	return false;
}