#include <stdlib.h>
#include <stdio.h>

#define MY_MIN(a, b) ((a) < (b) ? (a) : (b))

static int	bsq(FILE *file)
{
	int	line_count, width = 0, read_len, i_row, i_col, best_size = 0, best_row = 0, best_col = 0, current_val, diag_val, *dyn_arr;
	char	empty_c, obs_c, fill_c, *line_buf = 0, **grid;
	size_t	buf_cap = 0;

	if (fscanf(file, "%d %c %c %c", &line_count, &empty_c, &obs_c, &fill_c) != 4
		|| line_count < 1 || empty_c == obs_c || empty_c == fill_c
		|| obs_c == fill_c || empty_c <= ' ' || obs_c <= ' ' || fill_c <= ' '
		|| empty_c > '~' || obs_c > '~' || fill_c > '~')
		return (1);
	read_len = getline(&line_buf, &buf_cap, file);
	for (i_col = 0; i_col < read_len && (line_buf[i_col] == ' ' || line_buf[i_col] == '\t'); i_col++);
	if (i_col != read_len - 1 || line_buf[i_col] != '\n'
		|| !(grid = malloc(line_count * sizeof(char *))))
		return (free(line_buf), 1);
	for (i_row = 0; i_row < line_count; i_row++, line_buf = 0, buf_cap = 0) {
		read_len = getline(&line_buf, &buf_cap, file) - 1;
		for (i_col = 0; i_col < read_len && (line_buf[i_col] == empty_c || line_buf[i_col] == obs_c); i_col++);
		if (read_len < 1 || line_buf[read_len] != '\n' || i_col < read_len
			|| (i_row && read_len != width))
			break ;
		(grid[i_row] = line_buf)[(width = read_len)] = 0;
	}
	if (i_row < line_count || getline(&line_buf, &buf_cap, file) != -1
		|| !(dyn_arr = calloc(width, sizeof(int)))) {
		while (free(line_buf), i_row-- > 0)
			line_buf = grid[i_row];
		return (free(grid), 1);
	}
	for (free(line_buf), i_row = 0; i_row < line_count; i_row++)
		for (diag_val = 0, i_col = 0; i_col < width; i_col++, diag_val = current_val) {
			current_val = dyn_arr[i_col];
			dyn_arr[i_col] = grid[i_row][i_col] != empty_c ? 0
				: !i_row || !i_col ? 1
				: MY_MIN(MY_MIN(dyn_arr[i_col], dyn_arr[i_col - 1]), diag_val) + 1;
			if (dyn_arr[i_col] > best_size)
				best_size = dyn_arr[i_col], best_row = i_row, best_col = i_col;
		}
	for (i_row = best_row - best_size + 1; i_row <= best_row; i_row++)
		for (i_col = best_col - best_size + 1; i_col <= best_col; i_col++)
			grid[i_row][i_col] = fill_c;
	for (i_row = 0; i_row < line_count; i_row++)
		fprintf(stdout, "%s\n", grid[i_row]), free(grid[i_row]);
	return (free(grid), free(dyn_arr), 0);
}

int	main(int argc, char **argv)
{
	FILE	*file;
	int	idx = 0;

	if (argc < 2 && bsq(stdin))
		fputs("map error\n", stderr);
	while (++idx < argc) {
		if (!(file = fopen(argv[idx], "r")) || bsq(file))
			fputs("map error\n", stderr);
		else if (idx < argc - 1)
			fputs("\n", stdout);
		if (file)
			fclose(file);
	}
	return (0);
}
