#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern int	ret;
extern int	w;
extern int	h;
extern int	it;
extern char	**board;

char	**getB(char **board);
void	freeB(void);
char	**getC(char **copy);

void	display(char **board);

void	fillB(void);

void	iter(void);
int		countN(int i, int j, char **copy);
int		isIn(int y, int x);
