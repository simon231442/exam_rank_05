#ifndef LIFE_H
# define LIFE_H

# include <stdlib.h>
# include <unistd.h>

# define ALIVE 'O'
# define DEAD  ' '

typedef struct s_life
{
	int		w, h, iter;
	int		x, y, drawing;
	char	**b;
}	t_life;

int		life_init(t_life *g, int w, int h, int iter);
void	life_parse(t_life *g);
void	life_step(t_life *g);
void	life_print(t_life *g);
void	life_free(t_life *g);

#endif
