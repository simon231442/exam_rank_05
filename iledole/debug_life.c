#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	w, h, it;
int	ret = 0;
char	**board = NULL;

char**	allB(char **board);
void	freeB(char **board);
void	fillB(void);
void	display(char **board);
void	iter(void);
int	main(int ac, char *av[])
{
	if (ac != 4)
		return 1;
	w = atoi(av[1]);
	h = atoi(av[2]);
	it = atoi(av[3]);
	board = allB(board);
	fillB();
	for(int i = 0; i < 1/*it*/; ++i)
		iter();
	display(board);////////////////////
	freeB(board);
	return ret;
}

char**	allB(char **board)
{//void *calloc(size_t n, size_t size);
	board = calloc(h + 1, sizeof(char*));
	if (!board)
	{
		ret = 1;
		return NULL;
	}
	for (int i = 0; i < h; ++i)
	{
		board[i] = calloc(w + 1, sizeof(char));
		if (!board[i])
		{
			ret = 1;
			freeB(board);
			return NULL;
		}
		for (int j = 0; j < w; ++j)
		{
			board[i][j] = ' ';
		}
		board[i][w] = '\0';
	}
	return board;
}

void	freeB(char **board)
{
	int	i = 0;

	if (board)
	{
		while (board[i])
			free(board[i++]);
	}
	free(board);
}

void	fillB(void)
{//ssize_t read(int fd, void buf[.count], size_t count);
	char	buff;
	int	i = 0;
	int	j = 0;
	int	draw = 0;
	
	while (read(0, &buff, 1) == 1)
	{
		switch (buff)
		{
			case 'w' :
				if (i > 0)
					--i;
				break;
			case 's' :
				if (i + 1 < h)
					++i;
				break;
			case 'a' :
				if (j > 0)
					--j;
				break;
			case 'd' :
				if (j + 1 < w)
					++j;
				break;
			case 'x' :
				draw = !(draw);
				break;
			default :
				break;
		}
		if (draw)
			board[i][j] = 'O';
	}
}

void	display(char **board)
{
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)//int putchar(int c);
			putchar(board[i][j]);
		putchar('\n');
	}
}

char	**makeC(char **copy);
int	countN(int i, int j, char **copy);
void	iter(void)
{
	char	**copy = NULL;
	int	count;

	copy = makeC(copy);
	if (!copy)
		return ;
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			count = countN(i, j, copy);
			printf("count(%d, %d): %d\n", i, j, count);/////////////////
			if (board[i][j] == 'O')
			{
				if (!(count == 2 || count == 3))
					board[i][j] = ' ';
			}
			else if (count == 3)
				board[i][j] = 'O';
		}
		printf("%s\n", board[i]);/////////////
	}
	freeB(copy);
}

char	**makeC(char **copy)
{
	copy = allB(copy);
	if (!copy)
		return NULL;
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
			copy[i][j] = board[i][j];
	}
	return copy;
}

bool	isIn(int y, int x);
int	countN(int i, int j, char **copy)
{
	int count = 0;

	for (int dy = -1; dy <= 1; ++dy)
	{
		for (int dx = -1; dx <= 1; ++dx)
		{
			if (dy == 0 && dx == 0)
				continue;
			int y = i + dy;
			int x = j + dx;

			if (isIn(y, x) && copy[x][y] == 'O')
				++count;
		}
	}
	return count;
}

bool	isIn(int y, int x)
{
	return (y >= 0 && y < h && x >= 0 && x < w);
}
