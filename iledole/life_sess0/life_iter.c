#include "life.h"

void	iter(void)
{
	char	**copy = NULL;
	int		count = 0;
//	int		ct[3];

	copy = getC(copy);
	if (ret)
		return;
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			count = countN(i, j, copy);
//			ct[j] = count;//
			if (board[i][j] == 'O')
			{
				if (!(count == 3 || count == 2))
					board[i][j] = ' ';
			}
			else if (count == 3)
				board[i][j] = 'O';
		}
//		printf("%d %d %d\n", ct[0], ct[1],ct[2]);//
	}
//	display(copy);
	free(copy);
}

int		countN(int i, int j, char **copy)
{
	int		y = 0;
	int		x = 0;
	int		count = 0;
	for (int dy = -1; dy <= 1; ++dy)
		for (int dx = -1; dx <= 1; ++dx)
		{
			if (!dy && !dx)
				continue ;
			y = i + dy;
			x = j + dx;
			if (isIn(y, x) && copy[y][x] == 'O')
				++count;
		}
	return (count);
}

int		isIn(int y, int x)
{
	return (y >= 0 && y < h && x >= 0 && x < w);
}
