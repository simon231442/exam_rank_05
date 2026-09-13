#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int ac, char **av) {
	int		width, height, iter;
	int		pen_x, pen_y, pen_down;
	int		row, col, dy, dx, neighbors;
	char	*board, *next, *swap, command;

	if (ac != 4) return 1;

	// initialisation des variables.
	width = atoi(av[1]);
	height = atoi(av[2]);
	iter = atoi(av[3]);
	board = malloc(width * height);
	next = malloc(width * height);
	row = width * height;

	// remplir le board vide dabord.
	while (row-- > 0)
		board[row] = ' ';

	// traiter les caractere avec securite (pas bouger hors du board.)
	// dessiner aussi si le pen est down;
	// pen_down ^= 1;
	// Comment fonctionne XOR avec 1
	// XOR compare les bits un par un :
	// 0 ^ 1 = 1
	// 1 ^ 1 = 0
	pen_x = pen_y = pen_down = 0;
	while (read(0, &command, 1) == 1) {
		if 		(command == 'w' && pen_y > 0)			pen_y--;
		else if (command == 's' && pen_y < height - 1)	pen_y++;
		else if (command == 'a' && pen_x > 0)			pen_x--;
		else if (command == 'd' && pen_x < width - 1)	pen_x++;
		else if (command == 'x')						pen_down ^= 1;
		if (pen_down)
			board[pen_y * width + pen_x] = 'O';
	}

	while (iter-- > 0) {
		// ligne par ligne ---
		for (row = 0; row < height; row++)
			// colonne par colonne |
			for (col = 0; col < width; col++) {
				// ici on check les neighbors pour savoir le prochains etat.
				neighbors = 0;
				// delta y et delta x pour une case a droite, 
				// a gauche en haut a droite, etc..
				for (dy = -1; dy <= 1; dy++)
					for (dx = -1; dx <= 1; dx++)
						// (dy (0) || dx (0)) == 0 -> false donc on est dans la cellule au milieu
						if ((dy || dx)
								// on verifie que les case voisine sont a l'interieur du board.
								&& row + dy >= 0 && row + dy < height
								&& col + dx >= 0 && col + dx < width)
							// ici on calcule exactement la bonne case voisine et si elle est == 0
							// alors la condition est vrai et donc on +1 a neighbors;
							neighbors += board[(row + dy) * width + col + dx] == 'O';
				// c'est ici quon va chercher si la case actuelle ou on se trouve est un O ? 
				// si oui on check si elle survit (2 neighbor ou 3)
				// si non alors on doit savoir si elle a 3 neighbors pour devenir un O du coup
				// et le next[] va prendre son prochain etat (soit 'O' soit ' ')
				next[row * width + col] = board[row * width + col] == 'O' 
					// si board[actuel] == 'O' check si on a 2 ou 3 neighbors pour rester 'O'
					? (neighbors == 2 || neighbors == 3 ? 'O' : ' ')
					// si board[actuel] == ' ' check si on 3 neighbors pour devenir un 'O'
					: (neighbors == 3 ? 'O' : ' ');
			}
		// on actualise board a next
		// et next a board;
		swap = board;
		board = next;
		next = swap;
	}
	// on affiche le board final correctement diviser selon les row et col.
	for (row = 0; row < height; row++) {
		for (col = 0; col < width; col++)
			putchar(board[row * width + col]);
		putchar('\n');
	}
	free(board);
	free(next);
	return 0;
}

