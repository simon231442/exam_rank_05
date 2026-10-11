#include "bsq.h"

void	getM(void)
{//void *calloc(size_t n, size_t size);
	int r;

	map = calloc(h + 1, sizeof(int*));
	if (!map && ret++)
		return;
	for (int i = 0; i < h; ++i)
	{//ssize_t getline(char **restrict lineptr, size_t *restrict n, FILE *restrict stream);
		r = (int)getline(&line, &bit, file);
		if (i == 0)
			w = r - 1;
		if ((w + 1 != r || line[w] != '\n') && ret++)
			return;
		map[i] = calloc(w, sizeof(int));
		if (!map[i] && ret++)
			return;
		for (int j = 0; j < w; ++j)
		{
			if (line[j] == emp)
				map[i][j] = 1;
			else if (line[j] != obs && ret++)
				return;
		}
		free(line);
		line = NULL;
		bit = 0;
	}
}

void	freeM(void)
{
	int	i = 0;

	while(map && map[i])
		free(map[i++]);
	if (map)
		free(map);
}

