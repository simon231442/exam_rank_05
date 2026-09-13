#ifndef BSQ_H
# define BSQ_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct { int n; char e, o, f; }	t_el;
typedef struct { char **g; int w, h; }		t_map;
typedef struct { int s, y, x; }			t_sq;

int		bsq(FILE *fp);
void	free_map(t_map *m);

#endif
