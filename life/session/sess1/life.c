#include <unistd.h>
#include <stdlib.h>

int		width;
int		height;
int		iteration;
int		k;
int		l;
int		draw;
char**	board;

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
	return 0;
}




