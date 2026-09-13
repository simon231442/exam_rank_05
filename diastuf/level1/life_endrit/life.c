#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int		width, height, iterations;
	int		pen_x, pen_y, pen_down;
	int		row, col, neighbors, dy, dx;
	char	*board, *next, *swap, command;

	if (ac != 4)
		return 1;
	width = atoi(av[1]);
	height = atoi(av[2]);
	iterations = atoi(av[3]);
	board = malloc(width * height);
	next = malloc(width * height);
	row = width * height;
	while (row-- > 0)
		board[row] = ' ';
	pen_x = pen_y = pen_down = 0;
	while (read(0, &command, 1) == 1)
	{
		if      (command == 'w' && pen_y > 0)          pen_y--;
		else if (command == 's' && pen_y < height - 1) pen_y++;
		else if (command == 'a' && pen_x > 0)          pen_x--;
		else if (command == 'd' && pen_x < width - 1)  pen_x++;
		else if (command == 'x')                       pen_down ^= 1;
		if (pen_down)
			board[pen_y * width + pen_x] = 'O';
	}
	while (iterations-- > 0)
	{
		for (row = 0; row < height; row++)
			for (col = 0; col < width; col++)
			{
				neighbors = 0;
				for (dy = -1; dy <= 1; dy++)
					for (dx = -1; dx <= 1; dx++)
						if ((dy || dx) && row + dy >= 0 && row + dy < height
									   && col + dx >= 0 && col + dx < width)
							neighbors += board[(row + dy) * width + col + dx] == 'O';
				next[row * width + col] = board[row * width + col] == 'O'
					? (neighbors == 2 || neighbors == 3 ? 'O' : ' ')
					: (neighbors == 3 ? 'O' : ' ');
			}
		swap = board;
		board = next;
		next = swap;
	}
	for (row = 0; row < height; row++)
	{
		for (col = 0; col < width; col++)
			putchar(board[row * width + col]);
		putchar('\n');
	}
	free(board);
	free(next);
	return 0;
}
