#include <stdio.h>
#include <stdlib.h>

FILE	*file;
int		h;
char	emp;
char	obs;
char	full;
int		w;
char	*line = NULL;
size_t	bit = 0;
int		map[100][100];
int		one = 0;
int		lb = 0;
int		k;
int		l;

//int fprintf(FILE *stream, const char *format, ...);
void	printE(void) {fprintf(stdout, "map error\n");}

void	solve(void);
int		main(int ac, char *av[])
{
	if (ac < 2)
	{
		file = stdin;
		solve();
	}
	else if (ac == 2)
//FILE *fopen(const char *pathname, const char *mode);
	{
		file = fopen(av[1], "r");
		solve();
	}
	else
	{
		for (int i = 1; i < ac; ++i)
		{
			file = fopen(av[i], "r");
			solve();
		}
	}
	return 0;
}

int		setK(void);
int		parse(void);
void	findB(void);
void	solve(void)
{
	if (setK())
		return(printE());
	if (parse())
		return(printE());
	findB();
}

int		setK(void)
{
	int	ret = fscanf(file, "%d %c %c %c", &h, &emp, &obs, &full);
	//int fscanf(FILE *stream, const char *format, ...);
	if (ret != 4)
		return 1;
	if (h < 1)
		return 1;
	if (emp < 32 || obs < 32 || full < 32)
		return 1;
	if (emp > 126 || obs > 126 || full > 126)
		return 1;
	if (emp == obs || emp == full)
		return 1;
	if (obs == full)
		return 1;
//	printf("%d %c %c %c %d", h, emp, obs, full, ret);
	w = (int)getline(&line, &bit, file);
//	printf("%s",line);
	free(line);
	line = NULL;
	bit = 0;
	return 0;
}

int		fillM(int i);
int		parse(void)
{
	for (int i = 0; i < h; ++i)
	{
		if (i == 0)
			w = (int)getline(&line, &bit, file);
		else
		{
			if (w != (int)getline(&line, &bit, file))
			{
				free(line);
				return 1;
			}
		}
		if (fillM(i))
			return 1;
		free(line);
		line = NULL;
		bit = 0;
	}
	return 0;
}

int		fillM(int i)
{
	for (int j = 0; j < w; ++j)
	{
		if (line[i] == emp)
		{
			map[i][j] = 1;
			one = 1;
		}
		else if (line[i] == obs)
			map[i][j] = 0;
		else
			return 1;
	}
	return 0;
}

int		myMin(int i, int j);
void	findB(void)
{
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			if ((j == 0 || i == 0) && map[i][j])
				break;
			else if (map[i][j])
			{
				map[i][j] = myMin(i, j) + 1;
				if (map[i][j] > lb)
				{
					lb = map[i][j];
					k = i;
					l = j;
				}
			}
		}
	}
}

int		myMin(int i, int j)
{
	int	up;
	int dia;
	int le;
	int min;

	up = map[i - 1][j];
	dia = map[i - 1][j - 1];
	le = map[i][j - 1];
	min = (up <= dia) ? up : dia;
	min = (min <= le) ? min : le;
	return min;
}

//gerer le \n
//checker le one
