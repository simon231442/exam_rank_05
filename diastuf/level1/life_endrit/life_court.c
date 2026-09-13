#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc != 4)
		return 1;
	int width = atoi(argv[1]), height = atoi(argv[2]), iterations = atoi(argv[3]), stride = width + 2;
	char *board = calloc(stride * (height + 2), 1), *next = calloc(stride * (height + 2), 1), *swap, cmd;
	int x = 1, y = 1, pen_down = 0, sum, k;

	while (read(0, &cmd, 1) == 1)
	{
		x += (cmd == 'd' && x < width) - (cmd == 'a' && x > 1);
		y += (cmd == 's' && y < height) - (cmd == 'w' && y > 1);
		pen_down ^= (cmd == 'x');
		if (pen_down)
			board[y * stride + x] = 1;
	}
	while (iterations--)
	{
		for (y = 1; y <= height; y++)
			for (x = 1; x <= width; x++)
			{
				sum = 0;
				for (k = 0; k < 9; k++)
					sum += board[(y + k / 3 - 1) * stride + x + k % 3 - 1];
				next[y * stride + x] = (sum == 3 || (sum == 4 && board[y * stride + x]));
			}
		swap = board, board = next, next = swap;
	}
	for (y = 1; y <= height; y++, putchar('\n'))
		for (x = 1; x <= width; x++)
			putchar(board[y * stride + x] ? 'O' : ' ');
	free(board), free(next);
}
