#include "life.h"

char	**getB(char **board)
{//void *calloc(size_t nmemb, size_t size);
	board = calloc(h + 1, sizeof(char*));
	if (!board && ++ret)
		return NULL;
	for (int i = 0; i < h; ++i)
	{
		board[i] = calloc(w + 1, sizeof(char));
		if (!board[i] && ++ret)
			return NULL;
		for (int j = 0; j < w; ++j)
			board[i][j] = ' ';
	}
	return board;
}

void	freeB(void)
{
	int i = 0;

	while (board && board[i])
		free(board[i++]);
	if (board)
		free(board);
}

char	**getC(char **copy)
{
	copy = getB(copy);
	if (ret)
		return NULL;
	for (int i = 0; i < h; ++i)
		for (int j = 0; j < w; ++j)
			copy[i][j] = board[i][j];
	return copy;
}
