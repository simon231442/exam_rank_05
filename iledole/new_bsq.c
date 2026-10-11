#include <stdio.h>
#include <stdlib.h>

//printE
//main
//getK//k[3]
//getM//definir w a partir de r
//freeA
//solve
//m3//utiliser les arguments
//findB
//display
//isS

FILE	*file = NULL;
int	h;
int	w;
char	emp;
char	obs;
char	ful;
char	*line = NULL;
size_t	bit = 0;
int	**map = NULL;
int	lb = 0;
int	k = 0;
int	l = 0;

//int fprintf(FILE *restrict stream,const char *restrict format, ...);
void	printSE(void) {fprintf(stderr, "Sys error\n");}
void	printME(void) {fprintf(stderr, "map error\n");}
int	solve(void);
int	getK(void);
int	getM(void);
void	freeA(void);
void	findB(void);
void	display(void);

int	main(int ac, char **av)
{
	if (ac == 1)
		file = stdin;
	else if (ac == 2)
	{//FILE *fopen(const char *restrict pathname, const char *restrict mode);
		file = fopen(av[1], "r");
		if (file == NULL)
			return (printSE(), 1);
	}
	else
		return (printME(), 1);
	if (solve())
		return 1;
	if (file != stdin)
	{
		fclose(file);
	}
	return 0;
}

int 	solve(void)
{
	if (getK())
		return 1;
	if (getM())
		return (freeA(), 1);
	findB();
	display();
	return (freeA(), 0);
}

int	getK(void)
{//int fscanf(FILE *restrict stream, const char *restrict format, ...);
	if (fscanf(file, "%d%c%c%c", &h, &emp, &obs, &ful) != 4)
		return (printME(), 1);
	if (h < 1)
		return (printME(), 1);
	if (emp < 32 || obs < 32 || ful < 32)
		return (printME(), 1);
	if (emp > 126 || obs > 126 || ful > 126)
		return (printME(), 1);
	if (emp == obs || emp == ful || ful == obs)
		return (printME(), 1);
//ssize_t getline(char **restrict lineptr, size_t *restrict n, FILE *restrict stream);
	if (getline(&line, &bit, file) != 1)//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		return (free(line), printME(), 1);
	if (line[0] != '\n')
		return (free(line), printME(), 1);
	free(line);
	line = NULL;
	bit = 0;
	return 0;
}

int	getM(void)
{
//	int	tmpw = 0;
	w = getline(&line, &bit, file) - 1;
	if (line == NULL)
		return (free(line), printME(), 1);
//void *calloc(size_t n, size_t size);
	map = calloc(h + 1, sizeof(int*));
	if (!map)
		return (free(line), printSE(), 1);
	for (int i = 0; i < h; ++i)
	{
		map[i] = calloc(w, sizeof(int));
		if (!map[i])
			return (free(line), printSE(), 1);
	}
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			if (line[j] == obs)
				continue ;
			else if (line[j] == emp)
				map[i][j] = 1;
			else
				return (free(line), printME(), 1);
		}
		free(line);
		line = NULL;
		bit = 0;
		if (i + 1 == h)
			break;
		if (getline(&line, &bit, file) != w + 1)
			return (free(line), printME(), 1);
		if (line == NULL)
			return (printSE(), 1);
	}
	return 0;
}

void	freeA(void)
{
	int i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

int	minS(int i, int j);
void	findB(void)
{
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			if (i > 0 && j > 0 && map[i][j])
				map[i][j] = minS(i, j) + 1;
			if (map[i][j] > lb)
			{
				lb = map[i][j];
				k = i;
				l = j;
			}
		}
	}
}

int	minS(int i, int j)
{
	int	up;
	int	dia;
	int	le;
	int	min;

	up = map[i - 1][j];
	dia = map[i - 1][j - 1];
	le = map[i][j - 1];
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
			if (map[i][j] == 0)
				fprintf(stdout, "%c", obs);
			else
			{
				if (isS(i, j))
					fprintf(stdout, "%c", ful);
				else
					fprintf(stdout, "%c", emp);
			}
		}
		fprintf(stdout, "\n");
	}
}

int	isS(int i, int j)
{
	return (i <= k && i > k - lb && j <= l && j > l - lb);
}
