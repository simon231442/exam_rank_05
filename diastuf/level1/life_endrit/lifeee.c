#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	 main(int ac, char **av) {
	if (ac != 4) return 1;
	int w = atoi(av[1]), h = atoi(av[2]), i = atoi(av[3]), s = w + 2;
	char *b = calloc(s * (h + 2), 1), *n = calloc(s * (h + 2), 1), *sw, c;
	int x = 1, y = 1, pd = 0, sum, k;
	while (read(0, &c, 1)) {
		x += (c == 'd' && x < w) - (c == 'a' && x > 1);
		y += (c == 's' && y < h) - (c == 'w' && y > 1);
		pd ^= (c == 'x');
		if (pd)
			b[y * s + x] = 1;
	}
	while (i--) {
		for (y = 1; y <= h; y++)
			for (x = 1; x <= w; x++) {
				sum = 0;
				for (k = 0; k < 9; k++)
					sum += b[(y + k / 3 - 1) * s + x + k % 3 - 1];
				n[y * s + x] = (sum == 3 || (sum == 4 && b[y * s + x]));
			}
		sw = b, b = n, n = sw;
	}
	for (y = 1; y <= h; y++, putchar('\n'))
		for (x = 1; x <= w; x++)
			putchar(b[y * s + x] ? 'O' : ' ');
	free(b), free(n);
	return 0;
}
