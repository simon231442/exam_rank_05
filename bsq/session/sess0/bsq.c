#include <stdlib.h>
#include <stdio.h>

FILE	*file;
char	*line = NULL;
int		n;
char	em;
char	ob;
char	fu;
char	**map;
int		l;
int		**board;
int		lb = 0;
int		xb = 0;
int		yb = 0;

void	err(void) {fprintf(stderr, "map error\n"); }
void	freeA(void);
int		getK(void);
int		fillM(void);
int		getB(void);
int		findB(void);
void	display(void);

int main(int ac, char *av[])
{
	if (ac > 2)
		return (err(), 1);
	if (ac < 2)
		file = stdin;
	if (ac == 2)
	{
		file = fopen(av[1], "r");
		if (!file)
			return (err(), 1);
	}
	if (getK())
		return (err(), 1);
	if (fillM())
		return (err(), 1);
	if (getB())
		return (err(), 1);
	if (findB())
		return (err(), 1);
	display();
	freeA();
	return 0;
	//get et parse la 1 ligne
	//creer le tableau de de char
	//creer le tableau d'int
	//faire le dp
	//remplir tableau de char avec bsq
	//afficher
}

void	freeA(void)
{
	int		i = 0;

	while (map && map[i])
		free(map[i++]);
	free(map);
	while (board && board[i])
		free(board[i++]);
	free(board);
}

int		getK(void)
{
	size_t	size = 0;
	int		i = 0;

	getline (&line, &size, file);
	if (!line)
		return 1;
	if (line[i] < '1' || line[i] > '9')
		return 1;
	n = line[i++] - '0';
	if (!(line[i] < '1' || line[i] > '9'))
		n = n * 10 + line[i++] - '0';
	if (line[i++] != ' ')
		return 1;
	if (line[i] < 32 || line[i] > 126)
		return 1;
	em = line[i++];
	if (line[i++] != ' ')
		return 1;
	if (line[i] < 32 || line[i] > 126 || line[i] == em)
		return 1;
	ob = line[i++];
	if (line[i++] != ' ')
		return 1;
	if (line[i] < 32 || line[i] > 126 || line[i] == em || line[i] == ob)
		return 1;
	fu = line[i++];
//	fprintf(stdout, "%ld", size);
//	fprintf(stdout, "%d %c %c %c\n", n, em, ob, fu);
	free(line);
	return 0;
}

int		check(char* line);
int		fillM(void)
{
	size_t	size = 0;

	map = calloc(n, sizeof(char**));
	if (!map)
		return (freeA(), 1);
	l = (int)getline(&map[0], &size, file);
	if (l == -1)
		return (freeA(), 1);
	for (int i = 1; i < n; ++i)
	{
		if (l != getline(&map[i], &size, file) || l == -1 || check(map[i]))
			return (freeA(), 1);
	}
	return 0;
}

int		check(char* line)
{
	while (*line && *line != '\n')
	{
		if (*line != em || *line != ob || *line != fu)
			return (freeA(), 1);
		line++;
	}
	if (*line != '\n')
		return (freeA(), 1);
	return 0;
}

int		getB(void)
{
	board = calloc(n, sizeof(int **));
	if (!board)
		return (freeA(), 1);
	for (int i = 0; i < n; ++i)
	{
		board[i] = calloc(n, sizeof(int *));
		if (!board)
			return (freeA(), 1);
	}
	return 0;
}

int		getmin(int i, int j);
int		findB(void)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < l; ++j)
		{
			if (map[i][j] == em)
				continue;
			else if (i == 0 || j == 0)
				board[i][j] = 1;
			else
				board[i][j] = getmin(i, j) + 1;
			if (board[i][j] > lb)
			{
				lb = board[i][j];
				xb = j;
				yb = i;
			}
		}
	}
	if (lb == 0)
		return 1;
	return 0;
}

int		getmin(int i, int j)
{
	int up = board[i - 1][j];
	int dia = board[i - 1][j - 1];
	int le = board[i][j - 1];
	int min;

	min = (up < dia) ? up : dia;
	min = (min < le) ? min : le;
	return (min);
}

int		isS(int i, int j);
void	display(void)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < l; ++i)
		{
			if (isS(i, j))
				fprintf(stdout, "%c", fu);
			else
				fprintf(stdout, "%c", map[i][j]);
		}
		fprintf(stdout, "\n");
	}
}

int		isS(int i, int j)
{
	if (i < yb && i > yb -lb &&
			j < xb && j > xb -lb)
		return 1;
	return 0;
}




	
	



	
	//ssize_t getline(char **lineptr, size_t *n, FILE *stream);
