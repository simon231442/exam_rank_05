#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char *av[])
{
	if (ac != 2)
		return 1;

	FILE	*file;
	char	*line = NULL;
	size_t	n = 0;

	file = fopen(av[1], "r");
	while (getline(&line, &n, file) != -1)
	{
		printf("%s", line);
		free(line);
		line = NULL;
	}
	return 0;
}


//ssize_t getline(char **lineptr, size_t *n, FILE *stream);
