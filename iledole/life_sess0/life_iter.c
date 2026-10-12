#include "life.h"

void	iter(void)
{
	char	**copy;
	int		count = 0;

	copy = getC(copy);
	if (ret)
		return;
	for (int i = 0; i < h; ++i)
		for (int j = 0; j < w; ++j)
		{
			count = countN(i, j, copy);
			if (board[i][j] == 'O')
			{
				if (!(count == 3 || count == 2))
					board[i][j] = ' ';
			}
			else if (count == 3)
				board[i][j] = 'O';
		}
	free(copy);
}

int		count(int i, int j, char **copy)
{
	int		count = 0;
	return (count);
}
