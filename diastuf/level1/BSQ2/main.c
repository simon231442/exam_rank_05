#include "bsq.h"

int	main(int ac, char **av)
{
	FILE	*fp;
	int		i;

	if (ac < 2)
	{
		if (bsq(stdin))
			fprintf(stderr, "map error\n");
		return (0);
	}
	i = 0;
	while (++i < ac)
	{
		fp = fopen(av[i], "r");
		if (!fp || bsq(fp))
		{
			fprintf(stderr, "map error\n");
			if (fp)
				fclose(fp);
			continue ;
		}
		fclose(fp);
		if (i < ac - 1)
			fprintf(stdout, "\n");
	}
	return (0);
}
