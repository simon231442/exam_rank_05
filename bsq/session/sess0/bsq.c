#include <stdlib.h>
#include <stdio.h>

FILE	*file;
char	*line = NULL;
int		n;
char	em;
char	ob;
char	fu;

void	err(void) {fprintf(stderr, "map error\n"); }
int		getK(void);

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
	//get et parse la 1 ligne
	//creer le tableau de de char
	//creer le tableau d'int
	//faire le dp
	//remplir tableau de char avec bsq
	//afficher
}

int		getK(void)
{
	size_t	size;
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
	fprintf(stdout, "%d %c %c %c\n", n, em, ob, fu);
	return 0;
}



	
	//ssize_t getline(char **lineptr, size_t *n, FILE *stream);
