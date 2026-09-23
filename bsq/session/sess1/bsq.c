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

//int fprintf(FILE *stream, const char *format, ...);
void	printE(void) {fprintf(stdout, "map error\n"); return 1;}

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
void	solve(void)
{
	if (setK)
		return(printE());
}

int		setK(void)
{
	int	ret = fscanf(file, "%d %c %c %c", h, emp, obs, full);
	//ssize_t getline(char **lineptr, size_t *n, FILE *stream);
//	w = (int)getline(&line, &bit, file);
	//int fscanf(FILE *stream, const char *format, ...);
	
	return 0;
}

