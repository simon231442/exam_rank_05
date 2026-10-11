#include "bsq.h"

void	getK(void)
{//int fscanf(FILE *restrict stream, const char *restrict format, ...);
 //ssize_t getline(char **restrict lineptr, size_t *restrict n, FILE *restrict stream);
	if (fscanf(file, "%d%c%c%c", &h, &emp, &obs, &full) != 4 || h < 1 || emp == obs || emp == full || full == obs)
	{
		ret = 1;
		return;
	}
	if (emp < 32 || obs < 32 || full < 32)
	{
		ret = 1;
		return;
	}
	if (emp > 126 || obs > 126 || full > 126)
	{
		ret = 1;
		return;
	}
	if (getline(&line, &bit, file) != 1 || line[0] != '\n')
	{
		free(line);
		ret = 1;
		return ;
	}
	free(line);
	line = NULL;
	bit = 0;
}
