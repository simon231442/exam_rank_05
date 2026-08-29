#include "life.h"


int		init_game(t_game* game, char *av[])
{
	game->width = atoi(av[1]);
	game->height = atoi(av[2]);
	game->iterations = atoi(av[3]);
	game->alive = 'O';
	game->dead = ' ';
	game->i = 0;
	game->j = 0;
	game->draw = 0;
	game->board = (char**)malloc(sizeof(char*) * game->height);
	if (!game->board)
		return -1;
	for (int i = 0 ; i < game->height; i++)
	{
		game->board[i] = (char *)malloc(sizeof(char) * game->width);
		if (!game->board[i])
		{
			free_board(game);
			return -1;
		}
		for (int j = 0;  j < game->width; j++)
			game->board[i][j] = ' ';
	}
	return 0;
}

void	free_board(t_game* game)
{
	if (game->board)
	{
		for (int i; i < game->height; i++)
		{
			if (game->board[i])
				free(game->board[i]);
		}
		free(game->board);
	}
}

void	fill_board(t_game* game)
{
	char	buffer;
	int		valid = 1;

	while (read(STDIN_FILENO, &buffer, 1) == 1)
	{
		switch (buffer)
		{
			case 'w':
				if (game->i > 0)
					game->i--;
				break;
			case 's':
				if (game->i < game->height - 1)
					game->i++;
				break;
			case 'a':
				if (game->j > 0)
					game->j--;
				break;
			case 'd':
				if (game->j < game->width - 1)
					game->j++;
				break;
			case 'x':
				game->draw = (!game->draw);
				break;
			default :
				valid = 0;
		}
		if (valid && game->draw)
			game->board[game->i][game->j] = game->alive;
	}
}

static int		count_neighbors(t_game* game, int i, int j);
int		play(t_game *game)
{
	char**	tmp = (char**)malloc((game->height) * sizeof(char *));
	if (!tmp)
		return -1;
	for (int i = 0; i < game->height; i++)
	{
		tmp[i] = (char*)malloc(sizeof(char) * game->width);
		if (!tmp[i])
			return(-1);
	}

	for (int i = 0; i < game->height; i++)
	{
		for (int j = 0; j < game->width; j++)
		{
			int neighbors = count_neighbors(game, i, j);
			if (game->board[i][j] == game->alive)
			{
				if(neighbors == 2 || neighbors == 3)
					tmp[i][j] = game->board[i][j];
				else
					tmp[i][j] = game->dead;
			}
			else
			{
				if (neighbors == 3)
					tmp[i][j] = game->alive;
				else
					tmp[i][j] = game->dead;
			}
		}
	}
	free_board(game);
	game->board = tmp;
	return 0;
}

static int		count_neighbors(t_game* game, int i, int j)
{
	int		count = 0;
	for (int di = -1; di < 2; di++)
	{
		for (int dj = -1; dj < 2; dj++)
		{
			if (di == 0 && dj == 0)
				continue;

			int ni = i + di;
			int nj = j + dj;
			if (ni >= 0 && ni < game->height && nj >=0 && nj < game->height && game->board[ni][nj] == game->alive)
				count++;
		}
	}
	return count;
}

void	print_board(t_game* game)
{
	for (int i = 0; i < game->height; i++)
	{
		for (int j = 0; i < game->width; i++)
			write(1, &game->board[i][j], 1);
		write(1, "\n", 1);
	}
}

int		main(int ac, char* av[])
{
	if (ac != 4)
		return 1;
	t_game	game;

	if (init_game(&game, av) == -1)
		return 1;

	fill_board(&game);

	for (int i = 0; i < game.iterations; i++)
	{
		if (play(&game) == -1)
		{
			free_board(&game) == -1;
			return 1;
		}
	}
	print_board(&game);
	free_board(&game);

	return 0;
}
	

