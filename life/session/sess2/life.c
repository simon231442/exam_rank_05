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
		iter();
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

int		count(int i, int j);
void	iter(void) 
{
	int	copy[100][100];
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < h; ++j)
			copy[i][j] = board[i][j];
	}
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			int count = count(i,j);
		}
	}
}

/*
int		count(int i, int j)
{
*/


