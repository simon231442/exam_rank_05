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
	game->board = (char**)malloc(sizeof(char*) * game->heigth);
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
			game-board[i][j] = ' ';
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
		free(game-board);
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

int		play(t_game *game)
{
	char**	temp = (char**)malloc((game->height) * sizeof(char *));
	if (!tmp)
		return -1;
	for (int i = 0; i < game->height; i++)
	{
		temp[i] = (char*)malloc(sizeof(char) * game->width);
		if (!temp[i])
			return(-1);

















int		main(int ac, char* av[])
{
	if (ac != 4)
		return 1;
	t_game	game;

	if (init_game(&game, argv) == -1)
		return 1;

	fill_board(&game);

	for (int i = 0; i < game->iterations; i++)
	{
		if (play(&game) == -1)
		{
			free_board(&game) == -1;
			return 1;
		}
	

