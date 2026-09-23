#include <unistd.h>
#include <stdlib.h>
int w;
int	h;
int	it;
static int	board[100][100];

void	fillB(void);
void	display(void);
void	iter(void);

int		main(int ac, char *av[])
{
	if (ac != 4)
		return 1;
	w = atoi(av[1]);
	h = atoi(av[2]);
	it = atoi(av[3]);
	fillB();
	for (int i = 0; i < h; ++i)
	{
		display();
		iter();
	}
	display();
	return 0;
}


//ssize_t read(int fildes, void *buf, size_t nbyte);

void	fillB(void)
{
	char	c;
	int		draw = 0;
	int i = 0;
	int j = 0;
	while(1)
	{
		if (read(0, &c, 1) != 1)
			break;
		if (draw)
			board[i][j] = 1;
		switch(c)
		{
			case 'w':
				if (j > 0)
					--j;
				break;
			case 's':
				if (j + 1 < h)
					++j;
				break;
			case 'a':
				if (i > 0)
					--i;
				break;
			case 'd':
				if (i + 1 < w)
					++i;
				break;
			case 'x':
				draw = !(draw);
				break;
			default:
				break;
		}
	}
}
	
void	display(void)
{
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			if (board[i][j] == 0)
				write(1, " ", 1);
			if (board[i][j] == 1)
				write(1, "o", 1);
		}
		write(1, "\n", 1);
	}
}

int		count(int i, int j, int copy[][100]);
void	iter(void) 
{
	int	copy[100][100];
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
			copy[i][j] = board[i][j];
	}
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			int c = count(i, j, copy);
			if (board[i][j] == 1)
			{
				if (c == 2 || c == 3)
					board[i][j] = 1;
				else
					board[i][j] = 0;
			}
			if (board[i][j] == 1)
			{
				if (c == 3)
					board[i][j] = 1;
				else
					board[i][j] = 0;
			}

			/*
			if (board[i][j] == 1)
			{
				if (c == 2 || c == 3)
					continue;
				else
					board[i][j] = 0;
			}
			else if (board[i][j] == 0 && c == 3)
				board[i][j] = 1;
				*/
		}
	}
}

int		isIn(int x, int y);
int		count(int i, int j, int copy[][100])
{
	int count = 0;
	int y;
	int x;

	for (int dy = -1; dy <= 1; ++dy)
	{
		for (int dx = -1; dx <= 1; ++dx)
		{
			if (dy == 0 && dx == 0)
				continue;
			y = dy + i;
			x = dx + j;
			if (isIn(x, y) && copy[y][x])
				++count;
		}
	}
	return count;
}

int		isIn(int x, int y)
{
	return (x >= 0 && x < w && y >= 0 && y < h);
}


