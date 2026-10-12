#include "bsq.h"

FILE	*file = NULL;
int	ret = 0;
int	h;
int	w;
char	emp;
char	obs;
char	full;
char	*line = NULL;
size_t	bit = 0;
int	**map = NULL;
int	k = 0;
int	l = 0;
int	lb = 0;

int	main(int ac, char *av[])
{
	if (ac == 1)
		file = stdin;
	else if (ac == 2)
	{//FILE *fopen(const char *restrict pathname, const char *restrict mode);
		file = fopen(av[1], "r");
		if (!file && ++ret)
			goto end;
	}
	else if (++ret)
		goto end;
	getK();
	if (ret)
		goto end;
	getM();
	if (ret)
		goto end;
	findB();
	if (ret)
		goto end;
	display();
end :
	freeM();
	if (file && file != stdin)
		fclose(file);
	if (ret)
		fprintf(stderr, "map error\n");
	return ret;
}

void	display(void)
{
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{//int fputs(const char *s, FILE *stream);
			if (map[i][j] == 0)
				fprintf(stdout, "%c", obs);
			else
			{
				if (isS(i, j))
					fprintf(stdout, "%c", full);
				else
					fprintf(stdout, "%c", emp);
			}
		}
		fputs("\n", stdout);
	}
}

int			isS(int i, int j)
{
	return (i <= k && i > k - lb && j <= l && j > l - lb);
}

