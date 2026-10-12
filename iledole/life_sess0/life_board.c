#include "life.h"

void	fillB(void)
{
	int	i = 0;
	int j = 0;
	int draw = 0;
	char	buff;

	//ssize_t read(int fd, void *buf, size_t count);
	while(read(0, &buff, 1) == 1)
	{
		switch (buff)
		{
			case 'w':
				if(i > 0)
					i--;
				break;
			case 's':
				if (i + 1 < h)
					i++;
				break;
			case 'a':
				if (j > 0)
					j--;
				break;
			case 'd':
				if (j + 1 < w)
					j++;
				break;
			case 'x':
				draw = !(draw);
				break;
			default :
				break;
		}
		if (draw)
			board[i][j] = 'O';
	}
}

