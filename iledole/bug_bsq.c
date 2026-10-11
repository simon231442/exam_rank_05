#include <stdio.h>
#include <stdlib.h>

FILE	*file;
int	h;
int	w = 0;
char	emp;
char	obs;
char	full;
char	*line = NULL;
size_t	bit = 0;
int	map[100][100];
int	one = 1;
int	lb = 0;
int	k;
int	l;

//int fprintf(FILE *stream, const char *format, ...);
int	printE(void) {fprintf(stderr, "Error: invalid map\n\n"); return 1;}
int	solve(void);
int	main(int ac, char *av[])
{
	if (ac == 1)
	{
		file = stdin;
		if (solve())
			return(printE());
		fprintf(stdout, "\n");
		return 0;
	}
	else
	{
		for (int i = 1; i < ac; ++i)
		{
//FILE *fopen(const char *pathname, const char *mode);
			file = fopen(av[i], "r");
			if (solve())
				return(printE());
			fprintf(stdout, "\n");
		}
	}

	return 0;
}

int	getK(void);
int	getM(void);
void	findB(void);
void	display(void);
int	solve(void)
{
	if (getK())
		return 1;
	if (getM())
		return 1;
	findB();
	display();
	return 0;
}

int	getK(void)
{
	int	ret;

//int fscanf(FILE *stream, const char *format, ...);
	ret = fscanf(file,"%d%c%c%c", &h, &emp, &obs, &full);
	if (ret != 4)
		return 1;
	if (h < 1)
		return 1;
	if (emp < 32 || obs < 32 || full < 32)
		return 1;
	if (emp > 126 || obs > 126 || full > 126)
		return 1;
	if (emp == obs || emp == full || obs == full)
		return 1;
//ssize_t getline(char **lineptr, size_t *n, FILE *stream);
	w = (int)getline(&line, &bit, file);
	if (w != 1 && *line != '\n')
	{
		free(line);
		return 1;
	}
	w++;
	line = NULL;
	bit = 0;

	return 0;
}

int	getM(void)
{
	for (int i = 0; i < h; ++i)
	{
		if (i == 0)
		{
			w = (int)getline(&line, &bit, file);
			--w;
		}
		else
		{
			if (w != ((int)getline(&line, &bit, file) - 1))
			{
				free(line);
				return 1;
			}
		}
		if (line[w] != '\n')
		{
			free(line);			
			return 1;
		}
		for (int j = 0; j < w; ++j)
		{
			if (line[j] == emp)
			{
				one = 1;
				map[i][j] = 1;
			}
			else if (line[j] == obs)
				map[i][j] = 0;
			else
			{
				free(line);
				return 1;
			}
		}
		free(line);
		line = NULL;
		bit = 0;
	}
	if (!one)
		return 1;
	return 0;
}

//pourquoi pas voir coehrence h
int	myMin(int i, int j);
void	findB(void)
{
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			if ((i == 0 || j == 0) && map[i][j])
				map[i][j] = 1;
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

int	myMin(int i, int j)
{
	int up = map[i - 1][j];
	int dia = map[i - 1][j - 1];
	int le = map[i][j - 1];
	int min;

	min = (up <= dia) ? up : dia;
	min = (min <= le) ? min : le;
	return min;
}

int	isS(int i, int j);
void	display(void)
{
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			if (map[i][j] < 1)
				fprintf(stdout, "%c", obs);
			else
			{
				if (isS(i, j))
					fprintf(stdout, "%c", full);
				else
					fprintf(stdout, "%c", emp);
			}
		}
		fprintf(stdout, "\n");
	}
}

int	isS(int i, int j)
{
	return (i <= k && j <= l && i > (k - lb) && j > (l - lb));
}
