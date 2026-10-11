#pragma once

#include <stdlib.h>
#include <stdio.h>

extern FILE	*file;
extern int	ret;
extern int	h;
extern int	w;
extern char	emp;
extern char	obs;
extern char	full;
extern char	*line;
extern size_t	bit;
extern int	**map;
extern int	k;
extern int	l;
extern int	lb;

void	getK(void);
void	getM(void);
void	display(void);
void	freeM(void);
void	findB(void);
int	min3(int up, int dia, int le);
