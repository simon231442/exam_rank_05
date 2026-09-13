#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int		w, h, iter, x, y, draw, i, j, n, dy, dx;
	char	*g, *t, *s, c;

	if (ac != 4)
		return 1;
	w = atoi(av[1]);
	h = atoi(av[2]);
	iter = atoi(av[3]);
	g = malloc(w * h);
	t = malloc(w * h);
	i = w * h;
	while (i-- > 0) g[i] = ' ';
	x = y = draw = 0;
	while (read(0, &c, 1) == 1) {
		if      (c == 'w' && y > 0)     y--;
		else if (c == 's' && y < h - 1) y++;
		else if (c == 'a' && x > 0)     x--;
		else if (c == 'd' && x < w - 1) x++;
		else if (c == 'x')              draw ^= 1;
		if (draw) g[y * w + x] = 'O';
	}
	while (iter-- > 0) {
		for (i = 0; i < h; i++)
			for (j = 0; j < w; j++) {
				n = 0;
				for (dy = -1; dy <= 1; dy++)
					for (dx = -1; dx <= 1; dx++)
						if ((dy || dx) && i+dy >= 0 && i+dy < h
							&& j+dx >= 0 && j+dx < w)
							n += g[(i+dy)*w + j+dx] == 'O';
				t[i*w+j] = g[i*w+j] == 'O'
					? (n == 2 || n == 3 ? 'O' : ' ')
					: (n == 3 ? 'O' : ' ');
			}
		s = g; g = t; t = s;
	}
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++)
			putchar(g[i * w + j]);
		putchar('\n');
	}
	free(g);
	free(t);
	return 0;
}
