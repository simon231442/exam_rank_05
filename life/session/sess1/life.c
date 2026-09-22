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

int		free_all(void)
{
	for (int i = 0; i < height; ++i)
	{
		if (board[i])
			free(board[i]);
	}
	free(board);
	return 1;
}

void	copy(void);
void	count(int i, int j);
void	iter(void)
{
	int count = 0;
	copy();
	for (int i = 0; i < height ; ++i)
	{
		for (int j = 0 ; j < width ; ++j)
		{
			int n = count(i,j);
			if (board[i][j] == '0')
				if (count == 2 || count == 3)
					board
		}
}

void	copy(void)
{
	copyB = calloc(height, sizeof(char *));
	if (!copyB)
		return 1;
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

	for (dy = -1; dy <= 1; dy++)
	{
		for (dx = -1; dx <= 1; dx++)
		{
			int x = dx + j;
			int y = dy + i;
			if (isInside(x, y) && copyB[y][x] == '0')
				++res;
		}
	}
}

int		isInside(int x, int y)
{
	return (x >= 0 && x < width && y >= 0 && y < height);
}

/*
	if (i > 0)
	{
		if (copyb[i - 1][j] == 'o')
			++res;
		if (j > 0 && copyB[i - 1][j - 1] == 'o')
			++res;
		if (j + 1 < width && copyB[i + 1][j +1] == 'o')
			++res;
	}
	if (j > 0)
	{
		if (i + 1 < height && copyB[i + 1][j - 1] == 'o')
			++res;
		if (

	if (i - 1 > 0 && copyB[i - 1][j] == 'o')
		count++;
	if (i + 1 < height && copyB[i + 1][j] == 'o')
		count++;
	if (j - 1 > 0 && copyB[j - 1][j] == 'o')
		count++;
	if (j + 1 < width && copyB[j + 1][j] == 'o')
		count++;

	if (i - 1 > 0 && j - 1 > 0 && copyB[i - 1][j - 1] == 'o')
		count++;
	if (i - 1 > 0 &&
	if (i + 1 < height && copyB[i + 1][j] == 'o')
		count++;
		*/
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
			return free_all();
		for (int j = 0 ; j < width ; ++j)
			board[i][j] = ' ';
	}
	board_fill();
	for (int i = 0; i < iteration; ++i)
	{
		iter();
	}
	display();
	return 0;
}




