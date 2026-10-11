#include "bsq.h"

void	findB(void)
{
	for (int i = 0; i < h; ++i)
		for (int j = 0; j < w; ++j)
		{
			if (!(i == 0 || j == 0) && map[i][j])
				map[i][j] = min3(map[i - 1][j], map[i - 1][j - 1], map[i][j - 1]) + 1;
			if (map[i][j] > lb)
			{
				lb = map[i][j];
				k = i;
				l = j;
			}
		}
}

int	min3(int up, int dia, int le)
{
	up = (up < dia) ? up : dia;
	return (le < up) ? le : up;
}
	

