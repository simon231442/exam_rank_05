#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int	min(int a, int b) { return a < b ? a : b; }

static int	read_lines(FILE *f, char **g, int n, int *cols, char e, char o)
{
	char	buf[65536];
	int		i, j, len;

	for (i = 0; i < n; i++) {
		if (!fgets(buf, sizeof buf, f)) break;
		len = strlen(buf);
		if (len && buf[len - 1] == '\n') len--;
		buf[len] = '\0';
		if (!*cols) *cols = len;
		if (!len || len != *cols) break;
		for (j = 0; j < len; j++)
			if (buf[j] != e && buf[j] != o) break;
		if (j < len) break;
		if (!(g[i] = strdup(buf))) break;
	}
	if (i < n) { while (i-- > 0) free(g[i]); return -1; }
	return 0;
}

static int	bsq(FILE *f)
{
	char	e, o, fu;
	int		n, cols, i, j, best, bi, bj;

	if (fscanf(f, "%d %c %c %c\n", &n, &e, &o, &fu) != 4
		|| n < 1 || e == o || e == fu || o == fu)
		return -1;
	char	*g[n];
	cols = 0;
	if (read_lines(f, g, n, &cols, e, o))
		return -1;
	int		dp[n][cols];
	best = bi = bj = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < cols; j++) {
			dp[i][j] = 0;
			if (g[i][j] == e) {
				dp[i][j] = (i && j)
					? min(min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]) + 1 : 1;
				if (dp[i][j] > best) { best = dp[i][j]; bi = i; bj = j; }
			}
		}
	for (i = bi - best + 1; i <= bi; i++)
		for (j = bj - best + 1; j <= bj; j++)
			g[i][j] = fu;
	for (i = 0; i < n; i++)
		fprintf(stdout, "%s\n", g[i]), free(g[i]);
	return 0;
}

int	main(int ac, char **av)
{
	if (ac < 2)
		return bsq(stdin) ? (fputs("map error\n", stderr), 1) : 0;
	for (int i = 1; i < ac; i++) {
		FILE	*f = fopen(av[i], "r");
		int		ok = f && !bsq(f);
		if (!ok) fputs("map error\n", stderr);
		if (f) fclose(f);
		if (ok && i < ac - 1) putchar('\n');
	}
	return 0;
}
