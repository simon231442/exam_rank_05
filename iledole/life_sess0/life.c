#include "life.h"

int	ret;
int	w;
int	h;
int	it;
char	**board;

int		main(int ac, char *av[])
{
	ret = 0;
	if (ac != 4)
		return 1;
	w = atoi(av[1]);	
	h = atoi(av[2]);
	it = atoi(av[3]);

	board = getB(board);
	fillB();
	if (ret)
		goto end;
	for (int i = 0; i < it; ++i)
		iter();
	display(board);
end :
	freeB();
	return ret;
}

void	display(char **board)
{
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{//int putchar(int c);
			putchar(board[i][j]);
		}
		putchar('\n');
	}
}

