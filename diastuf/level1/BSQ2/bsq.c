#include "bsq.h"

/* --- helpers ------------------------------------------------------------- */

#define MIN(a,b) ((a)<(b)?(a):(b))

void	free_map(t_map *m)
{
	int	i;

	if (!m || !m->g)
		return ;
	i = -1;
	while (m->g[++i])
		free(m->g[i]);
	free(m->g);
	m->g = 0;
}

static int	printable(int c) { return (c >= 32 && c <= 126); }

/* --- parse elements (first line) ----------------------------------------- */

static int	parse_el(FILE *fp, t_el *el)
{
	if (fscanf(fp, "%d %c %c %c\n", &el->n, &el->e, &el->o, &el->f) != 4)
		return (-1);
	if (el->n <= 0)
		return (-1);
	if (el->e == el->o || el->e == el->f || el->o == el->f)
		return (-1);
	if (!printable(el->e) || !printable(el->o) || !printable(el->f))
		return (-1);
	return (0);
}

/* --- parse map lines ----------------------------------------------------- */

static char	*ft_strndup(char *s, int len)
{
	char	*dst;
	int		i;

	dst = malloc(len + 1);
	if (!dst)
		return (0);
	i = -1;
	while (++i < len)
		dst[i] = s[i];
	dst[len] = '\0';
	return (dst);
}

static int	valid_chars(char **g, char e, char o)
{
	int	i, j;

	i = -1;
	while (g[++i])
	{
		j = -1;
		while (g[i][++j])
			if (g[i][j] != e && g[i][j] != o)
				return (0);
	}
	return (1);
}

static int	parse_map(FILE *fp, t_map *m, t_el *el)
{
	char	*ln;
	size_t	lcap;
	int		rd, i;

	m->g = calloc(el->n + 1, sizeof(char *));
	if (!m->g)
		return (-1);
	ln = 0;
	lcap = 0;
	i = 0;
	while (i < el->n)
	{
		rd = getline(&ln, &lcap, fp);
		if (rd < 1 || ln[rd - 1] != '\n')
			return (free(ln), free_map(m), -1);
		rd--;
		m->g[i] = ft_strndup(ln, rd);
		if (!m->g[i])
			return (free(ln), free_map(m), -1);
		if (!i)
			m->w = rd;
		else if (m->w != rd)
			return (free(ln), free_map(m), -1);
		i++;
	}
	free(ln);
	if (!valid_chars(m->g, el->e, el->o))
		return (free_map(m), -1);
	m->h = el->n;
	return (0);
}

/* --- dynamic programming: find biggest square ---------------------------- */

static void	find_sq(t_map *m, t_el *el, t_sq *sq)
{
	int	dp[m->h][m->w];
	int	i, j, v;

	i = -1;
	while (++i < m->h)
	{
		j = -1;
		while (++j < m->w)
		{
			dp[i][j] = 0;
			if (m->g[i][j] != el->o)
			{
				if (!i || !j)
					dp[i][j] = 1;
				else
				{
					v = MIN(dp[i-1][j], dp[i][j-1]);
					v = MIN(v, dp[i-1][j-1]);
					dp[i][j] = v + 1;
				}
			}
			if (dp[i][j] > sq->s)
			{
				sq->s = dp[i][j];
				sq->y = i - sq->s + 1;
				sq->x = j - sq->s + 1;
			}
		}
	}
}

/* --- fill and print ------------------------------------------------------ */

static void	fill_print(t_map *m, t_el *el, t_sq *sq)
{
	int	i, j;

	i = sq->y - 1;
	while (++i < sq->y + sq->s)
	{
		j = sq->x - 1;
		while (++j < sq->x + sq->s)
			m->g[i][j] = el->f;
	}
	i = -1;
	while (++i < m->h)
		fprintf(stdout, "%s\n", m->g[i]);
}

/* --- orchestrator -------------------------------------------------------- */

int	bsq(FILE *fp)
{
	t_el	el;
	t_map	map;
	t_sq	sq;

	if (parse_el(fp, &el))
		return (-1);
	if (parse_map(fp, &map, &el))
		return (-1);
	sq = (t_sq){0, 0, 0};
	find_sq(&map, &el, &sq);
	fill_print(&map, &el, &sq);
	free_map(&map);
	return (0);
}
