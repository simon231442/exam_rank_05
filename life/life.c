/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:40:02 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/02/16 22:22:41 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life1.h"

t_grid	*create_grid(int width, int height)
{
	t_grid	*grid = (t_grid *)malloc(sizeof(t_grid));
	if (!grid)
		return (NULL);
	grid->width = width;
	grid->height = height;
	grid->cells = (int **)malloc(sizeof(int *) * height);
	if (!grid->cells)
	{
		free(grid);
		return (NULL);
	}
	for (int i = 0; i < height; i++)
	{
		grid->cells[i] = (int *)calloc(width, sizeof(int));
		if (!grid->cells[i])
		{
			for (int j = 0; j < i; j++)
				free(grid->cells[j]);
			free(grid->cells);
			free(grid);
			return (NULL);
		}
	}
	return (grid);
}

void	free_grid(t_grid *grid)
{
	if (!grid)
		return ;
	if (grid->cells)
	{
		for (int i = 0; i < grid->height; i++)
		{
			if (grid->cells[i])
				free(grid->cells[i]);
		}
		free(grid->cells);
	}
	free(grid);
}

int	is_inside(int x, int y, t_grid *grid)
{
	return (x >= 0 && x < grid->width && y >= 0 && y < grid->height);
}

void	mark_cell(int x, int y, t_grid *grid)
{
	if (is_inside(x, y, grid))
		grid->cells[y][x] = 1;
}

void	draw_line(int x1, int y1, int x2, int y2, t_grid *grid)
{
	if (y1 == y2)
	{
		int start = (x1 < x2) ? x1 : x2;
		int	end = (x1 < x2) ? x2 : x1;
		for (int x = start; x <= end; x++)
			mark_cell(x, y1, grid);
	}
	else if (x1 == x2)
	{
		int	start = (y1 < y2) ? y1 : y2;
		int	end = (y1 < y2) ? y2 : y1;
		for (int y = start; y <= end; y++)
			mark_cell(x1, y, grid);
	}
}

void	execute_command(char cmd, t_pen *pen, t_grid *grid)
{
	int	old_x = pen->x;
	int	old_y = pen->y;

	if (cmd == 'w')
		pen->y--;
	else if (cmd == 's')
		pen->y++;
	else if (cmd == 'a')
		pen->x--;
	else if (cmd == 'd')
		pen->x++;
	else if (cmd == 'x')
	{
		pen->is_down = !pen->is_down;
		if (pen->is_down)
			mark_cell(pen->x, pen->y, grid);
		return ;
	}
	if (pen->is_down)
		draw_line(old_x, old_y, pen->x, pen->y, grid);
}

void	read_and_execute_commands(t_grid *grid)
{
	t_pen	pen;

	pen.x = 0;
	pen.y = 0;
	pen.is_down = 0;
	
	char	buffer;

	while (read(0, &buffer, 1) > 0)
		execute_command(buffer, &pen, grid);
}

int	count_neighbors(int x, int y, t_grid *grid)
{
	int	count = 0;

	for (int dy = -1; dy <= 1; dy++)
	{
		for (int dx = -1; dx <= 1; dx++)
		{
			if (dy == 0 && dx == 0)
				continue ;
			
			int	ny = y + dy;
			int	nx = x + dx;
			
			if (is_inside(nx, ny, grid) && grid->cells[ny][nx] == 1)
				count++;
		}
	}
	return (count);
}

void	generate_iteration(t_grid *current, t_grid *next)
{
	for (int y = 0; y < current->height; y++)
	{
		for (int x = 0; x < current->width; x++)
		{
			int	neighbors = count_neighbors(x, y, current);
			int	is_alive = current->cells[y][x];

			if (is_alive)
			{
				if (neighbors == 2 || neighbors == 3)
					next->cells[y][x] = 1;
				else
					next->cells[y][x] = 0;
			}
			else
			{
				if (neighbors == 3)
					next->cells[y][x] = 1;
				else
					next->cells[y][x] = 0;
			}
		}
	}
}

void	copy_grid(t_grid *src, t_grid *dst)
{
	for (int y = 0; y < src->height; y++)
	{
		for (int x = 0; x < src->width; x++)
			dst->cells[y][x] = src->cells[y][x];
	}
}

void	print_grid(t_grid *grid)
{
	for (int y = 0; y < grid->height; y++)
	{
		for (int x = 0; x < grid->width; x++)
		{
			if (grid->cells[y][x] == 1)
				putchar('O');
			else
				putchar(' ');
		}
		putchar('\n');
	}
}

int	main(int ac, char **av)
{	
	if (ac != 4)
		return (1);

	int	width = atoi(av[1]);
	int	height = atoi(av[2]);
	int	iteration = atoi(av[3]);
	
	t_grid	*current = create_grid(width, height);
	t_grid	*next = create_grid(width, height);

	if (!current || !next)
	{
		free_grid(current);
		free_grid(next);
		return (1);
	}
	read_and_execute_commands(current);
	for (int i = 0; i < iteration; i++)
	{
		generate_iteration(current, next);
		copy_grid(next, current);
	}
	print_grid(current);
	free_grid(current);
	free_grid(next);
	return (0);
}