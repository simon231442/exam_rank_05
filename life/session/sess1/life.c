#include <unistd.h>
#include <stdlib.h>

int		width;
int		height;
int		iteration;
int		k;
int		l;
int		draw;
char**	board;
char**	copyB;

void	free_all(void)
{
	for (int i = 0; i < height; ++i)
	{
		if (board[i])
			free(board[i]);
	}
	free(board);
}

void	copy(void);
int		count(int i, int j);
void	iter(void)
{
	int c = 0;
	copy();
	for (int i = 0; i < height ; ++i)
	{
		for (int j = 0 ; j < width ; ++j)
		{
			c = count(i,j);
			if (board[i][j] == '0')
				if (c == 2 || c == 3)
					continue;
				else
					board[i][j] = ' ';
			else
				if (c ==  3)
					board[i][j] = 'o';
		}
	}
	for (int i = 0; i < height; ++i)
		free(copyB[i]);
	free(copyB);
}

void	copy(void)
{
	copyB = calloc(height, sizeof(char *));
	if (!copyB)
		return;
	for (int i = 0; i < height ; ++i)
	{
		copyB[i] = calloc(width, sizeof(char));
		if (!copyB[i])
			return free_all();
		for (int j = 0 ; j < width ; ++j)
			copyB[i][j] = board[i][j];
	}
}

int		isInside(int x, int y);
int		count(int i, int j)
{
	int res = 0;

	for (int dy = -1; dy <= 1; dy++)
	{
		for (int dx = -1; dx <= 1; dx++)
		{
			int x = dx + j;
			int y = dy + i;
			if (isInside(x, y) && copyB[y][x] == '0')
				++res;
		}
	}
	return 1;
}

int		isInside(int x, int y)
{
	return (x >= 0 && x < width && y >= 0 && y < height);
}

void	board_fill(void)
{
	char	buffer;

	while (read(STDIN_FILENO, &buffer, 1) == 1)
	{
		switch (buffer)
		{
			case 'w' :
				if (k > 0)
					k--;
				break;
			case 's' :
				if (k < height - 1)
					k++;
				break;
			case 'a' :
				if (l > 0)
					l--;
				break;
			case 'd' :
				if (l < height - 1)
					l++;
				break;
			case 'x' :
				draw = !(draw);
				break;
			default :
				return ;
		}
	if (draw)
		board[k][l] = 'O';
	}
}

void	display(void)
{
	for (int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width; ++j)
			write(1, &board[i][j], 1);
		write(1, "\n", 1);
	}
}

int		main(int ac, char *av[])
{
	if (ac != 4)
		return 1;
	width = atoi(av[1]);
	height = atoi(av[2]);
	iteration = atoi(av[3]);
	board = calloc(height, sizeof(char *));
	if (!board)
		return 1;
	for (int i = 0; i < height ; ++i)
	{
		board[i] = calloc(width, sizeof(char));
		if (!board[i])
			return (free_all(), 1);
		for (int j = 0 ; j < width ; ++j)
			board[i][j] = ' ';
	}
	board_fill();
	for (int i = 0; i < iteration; ++i)
		iter();
	display();
	return 0;
}




