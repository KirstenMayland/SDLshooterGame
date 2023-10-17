#include "util.h"

int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	return (fmax(x1, x2) < fmin(x1 + w1, x2 + w2)) && (fmax(y1, y2) < fmin(y1 + h1, y2 + h2));
}

void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy)
{
	int steps = fmax(abs(x1 - x2), abs(y1 - y2));

	if (steps == 0)
	{
		*dx = *dy = 0;
		return;
	}

	*dx = (x1 - x2);
	*dx /= steps;

	*dy = (y1 - y2);
	*dy /= steps;
}