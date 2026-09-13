#include "life.h"

/* --- alloc / free -------------------------------------------------------- */

int	life_init(t_life *g, int w, int h, int iter)
{
	int	i, j;

	g->w = w;
	g->h = h;
	g->iter = iter;
	g->x = 0;
	g->y = 0;
	g->drawing = 0;
	g->b = malloc(h * sizeof(char *));
	if (!g->b)
		return (-1);
	i = -1;
	while (++i < h)
	{
		g->b[i] = malloc(w);
		if (!g->b[i])
			return (life_free(g), -1);
		j = -1;
		while (++j < w)
			g->b[i][j] = DEAD;
	}
	return (0);
}

void	life_free(t_life *g)
{
	int	i;

	if (!g->b)
		return ;
	i = -1;
	while (++i < g->h)
		free(g->b[i]);
	free(g->b);
	g->b = 0;
}

/* --- stdin parsing ------------------------------------------------------- */

void	life_parse(t_life *g)
{
	char	c;

	while (read(0, &c, 1) == 1)
	{
		if (c == 'w' && g->y > 0)
			g->y--;
		else if (c == 's' && g->y < g->h - 1)
			g->y++;
		else if (c == 'a' && g->x > 0)
			g->x--;
		else if (c == 'd' && g->x < g->w - 1)
			g->x++;
		else if (c == 'x')
			g->drawing = !g->drawing;
		if (g->drawing)
			g->b[g->y][g->x] = ALIVE;
	}
}

/* --- conway -------------------------------------------------------------- */

static int	neighbors(t_life *g, int y, int x)
{
	int	dy, dx, n;

	n = 0;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (!dy && !dx)
				;
			else if (y + dy >= 0 && y + dy < g->h
				&& x + dx >= 0 && x + dx < g->w
				&& g->b[y + dy][x + dx] == ALIVE)
				n++;
			dx++;
		}
		dy++;
	}
	return (n);
}

void	life_step(t_life *g)
{
	char	**tmp;
	int		i, j, n;

	tmp = malloc(g->h * sizeof(char *));
	if (!tmp)
		return ;
	i = -1;
	while (++i < g->h)
		tmp[i] = malloc(g->w);
	i = -1;
	while (++i < g->h)
	{
		j = -1;
		while (++j < g->w)
		{
			n = neighbors(g, i, j);
			if (g->b[i][j] == ALIVE)
				tmp[i][j] = (n == 2 || n == 3) ? ALIVE : DEAD;
			else
				tmp[i][j] = (n == 3) ? ALIVE : DEAD;
		}
	}
	life_free(g);
	g->b = tmp;
}

/* --- output -------------------------------------------------------------- */

void	life_print(t_life *g)
{
	int	i, j;

	i = -1;
	while (++i < g->h)
	{
		j = -1;
		while (++j < g->w)
			write(1, &g->b[i][j], 1);
		write(1, "\n", 1);
	}
}

/* --- main ---------------------------------------------------------------- */

int	main(int ac, char **av)
{
	t_life	g;
	int		i;

	if (ac != 4)
		return (1);
	if (life_init(&g, atoi(av[1]), atoi(av[2]), atoi(av[3])))
		return (1);
	life_parse(&g);
	i = -1;
	while (++i < g.iter)
		life_step(&g);
	life_print(&g);
	life_free(&g);
	return (0);
}
