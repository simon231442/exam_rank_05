#include <stdlib.h>
#include <stdio.h>

typedef struct s_map
{
	int		rows;
	int		cols;
	char	empty;
	char	obstacle;
	char	full;
	char	**grid;
}	t_map;

static void	free_grid(char **grid, int rows)
{
	while (rows-- > 0)
		free(grid[rows]);
	free(grid);
}

static int	min3(int a, int b, int c)
{
	if (b < a)
		a = b;
	if (c < a)
		a = c;
	return (a);
}

static int	is_printable(char c)
{
	return (c > ' ' && c <= '~');
}

/* first line: "<rows> <empty> <obstacle> <full>\n" */
static int	parse_header(FILE *f, t_map *m)
{
	if (fscanf(f, "%d %c %c %c", &m->rows, &m->empty,
			&m->obstacle, &m->full) != 4)
		return (-1);
	if (m->rows < 1 || fgetc(f) != '\n')
		return (-1);
	if (!is_printable(m->empty) || !is_printable(m->obstacle)
		|| !is_printable(m->full))
		return (-1);
	if (m->empty == m->obstacle || m->empty == m->full
		|| m->obstacle == m->full)
		return (-1);
	return (0);
}

/* rows lines: same length, only empty/obstacle chars, then EOF */
static int	parse_grid(FILE *f, t_map *m)
{
	char	*line;
	size_t	cap;
	int		len;
	int		i;
	int		j;

	m->grid = calloc(m->rows, sizeof(char *));
	if (!m->grid)
		return (-1);
	for (i = 0; i < m->rows; i++)
	{
		line = NULL;
		cap = 0;
		len = (int)getline(&line, &cap, f);
		m->grid[i] = line;
		if (len < 2 || line[len - 1] != '\n')
			return (-1);
		line[--len] = '\0';
		if (i == 0)
			m->cols = len;
		if (len != m->cols)
			return (-1);
		for (j = 0; j < len; j++)
			if (line[j] != m->empty && line[j] != m->obstacle)
				return (-1);
	}
	line = NULL;
	cap = 0;
	if (getline(&line, &cap, f) != -1)
		return (free(line), -1);
	return (free(line), 0);
}

/* dp[j] = side of the biggest square whose bottom-right corner is (i, j) */
static int	solve(t_map *m)
{
	int	*dp;
	int	i;
	int	j;
	int	up_left;
	int	saved;
	int	best = 0;
	int	best_i = 0;
	int	best_j = 0;

	dp = calloc(m->cols, sizeof(int));
	if (!dp)
		return (-1);
	for (i = 0; i < m->rows; i++)
	{
		up_left = 0;
		for (j = 0; j < m->cols; j++)
		{
			saved = dp[j];
			if (m->grid[i][j] != m->empty)
				dp[j] = 0;
			else if (i == 0 || j == 0)
				dp[j] = 1;
			else
				dp[j] = min3(dp[j], dp[j - 1], up_left) + 1;
			up_left = saved;
			if (dp[j] > best)
			{
				best = dp[j];
				best_i = i;
				best_j = j;
			}
		}
	}
	for (i = best_i - best + 1; i <= best_i; i++)
		for (j = best_j - best + 1; j <= best_j; j++)
			m->grid[i][j] = m->full;
	return (free(dp), 0);
}

static int	handle_map(FILE *f)
{
	t_map	m;
	int		i;

	if (parse_header(f, &m))
		return (-1);
	if (parse_grid(f, &m) || solve(&m))
		return (free_grid(m.grid, m.rows), -1);
	for (i = 0; i < m.rows; i++)
		fprintf(stdout, "%s\n", m.grid[i]);
	return (free_grid(m.grid, m.rows), 0);
}

int	main(int argc, char **argv)
{
	FILE	*f;
	int		i;

	if (argc < 2)
	{
		if (handle_map(stdin))
			fputs("map error\n", stderr);
		return (0);
	}
	for (i = 1; i < argc; i++)
	{
		f = fopen(argv[i], "r");
		if (!f || handle_map(f))
			fputs("map error\n", stderr);
		if (f)
			fclose(f);
		if (i < argc - 1)
			fputs("\n", stdout);
	}
	return (0);
}
