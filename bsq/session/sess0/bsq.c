#include <stdlib.h>
#include <stdio.h>

FILE	*file;
char	*ligne;

void	err(void) {fprintf(stderr, "map error\n"); }

int main(int ac, char *av[])
{
	if (ac > 2)
		return (err(), 1);
	if (ac < 2)
		file = stdin;
	if (ac == 2)
	{
		file = fopen(av[1], r);
		if (!file)
			return (err(), 1);
	}
	//get et parse la 1 ligne
	//creer le tableau de de char
	//creer le tableau d'int
	//faire le dp
	//remplir tableau de char avec bsq
	//afficher
}

