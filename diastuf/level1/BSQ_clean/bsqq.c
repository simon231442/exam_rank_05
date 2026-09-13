#include <stdlib.h>
#include <stdio.h>

typedef struct s_map {
	int		rows;
	int		cols;
	char	empty;
	char	obstacle;
	char	full;
	char	**grid;
}	t_map;

static void free_grid(char **grid, int rows) {
	while (rows-- > 0)
		free(grid[rows]);
	free(grid);
}

static int min3(int a, int b, int c) {
	if (b < a)
		a = b;
	if (c < a)
		a = c;
	return a;
}

static int is_printable(char c) {
	return (c > ' ' && c <= '~');
}

static int	parse_header(FILE *f, t_map *m) {
	if (fscanf(f, "%d %c %c %c", &m->rows, &m->empty, &m->obstacle, &m->full) != 4)
		return -1;
	if (m->rows < 1 || fgetc(f) != '\n')
		return -1;
	if (!is_printable(m->empty) || !is_printable(m->obstacle)
		|| !is_printable(m->full))
		return -1;
	if (m->empty == m->obstacle || m->empty == m->full
		|| m->full == m->obstacle)
		return -1;
	return 0;
}

static int	parse_grid(FILE *f, t_map *m) {
	m->grid = calloc(m->rows, sizeof(char *));
	if (!m->grid)
		return -1;

}

static int	handle_map(FILE *f) {
	t_map	m;
	int		i;
	
	if (parse_header(f, &m))
		return -1;
	if (parse_grid(f, &m) || solve(&m))
		return (free_grid(m.grid, m.rows), -1);
	for (i = 0; i < m.rows; i++)
		fprintf(stdout, "%s\n", m.grid[i]);
	return (free_grid(m.grid, m.rows));
}

int main(int ac, char **av) {
	FILE	*f;
	int		i;

	if (ac < 2) {
		if (handle_map(stdin))
			fputs("map error\n", stderr);
		return 0;
	}

	for (i = 1; i < ac; i++) {
		f = fopen(av[i], "r");
		if (!f || handle_map(f))
			fputs("map error\n", stderr);
		if (f)
			fclose(f);
		if (i < ac - 1)
			fputs("\n", stdout);
	}
	return 0;
}
