# Guide complet : Life (sans `.h`, sans `struct`)

## Fichiers fournis (aucun — projet from scratch)

Le sujet ne fournit aucun fichier de départ. Tu pars d'une page blanche.

## Fichiers à créer (ce que tu rends)

```
life.c
```

Un seul fichier. Pas de `.h`, pas de `struct` — tout passe par des variables globales.
(Si "Expected files" exige explicitement `*.c *.h`, voir la section finale.)

---

## Rappel des règles du jeu (jamais explicitées dans le sujet)

Le sujet dit juste *"simulate a game of life"* — référence implicite à Conway (1970),
il faut connaître ses règles sans qu'elles soient redonnées :

| État actuel | Voisines vivantes | Résultat |
|---|---|---|
| Vivante | 0 ou 1 | meurt (sous-population) |
| Vivante | 2 ou 3 | reste vivante |
| Vivante | 4 à 8 | meurt (surpopulation) |
| Morte | 3 (exactement) | naît |
| Morte | tout autre nombre | reste morte |

**Moyen mnémotechnique** : 2 → statu quo, 3 → toujours vivante, tout le reste → morte.

---

## Structure du programme

```
main()
  ├── init_board()        alloue et vide le plateau
  ├── read_commands()     lit stdin, déplace le curseur, marque les cases
  ├── play()               applique les itérations
  │     └── compute_generation()
  │           └── count_neighbors()
  └── print_board()        affiche le résultat avec putchar
```

Pas d'héritage, pas de polymorphisme ici — mais la même logique de "chaque fonction a
un seul job" s'applique : chaque étape ci-dessous correspond à une fonction, testable
indépendamment.

---

## Technique centrale : variables globales à la place d'une `struct`

Quand tout l'état (dimensions, position du curseur, plateau) est partagé par toutes les
fonctions du fichier, une `struct` passée par pointeur n'apporte rien de plus qu'un jeu
de variables globales — sauf de la frappe en plus (`game->` partout). Sous pression
d'examen, ça se traduit par :

```
struct + pointeur  =>  game->i, game->j, game->board, un .h à maintenir
variables globales  =>  g_i, g_j, g_board, accessibles partout sans déréférencement
```

Contrepartie assumée : cette approche ne passerait pas un vrai audit de norme 42 hors
examen (état global mutable), mais reste parfaitement défendable pour un petit programme
autonome d'une centaine de lignes en temps limité.

---

## Étape 1 : déclarations globales et allocation

```c
#include <stdlib.h>
#include <unistd.h>

int   g_width;
int   g_height;
int   g_iterations;
int   g_i;
int   g_j;
int   g_draw;
char  **g_board;

int init_board(void)
{
	g_board = (char **)malloc(sizeof(char *) * g_height);
	if (!g_board)
		return (-1);
	for (int i = 0; i < g_height; i++)
	{
		g_board[i] = (char *)malloc(sizeof(char) * g_width);
		if (!g_board[i])
			return (-1);
		for (int j = 0; j < g_width; j++)
			g_board[i][j] = ' ';
	}
	return (0);
}
```

Points clés :
- `g_i`/`g_j` remplacent `game->i`/`game->j` : position du curseur, démarrent à `0`
- `g_draw` remplace `game->draw` : `0` = crayon levé, `1` = crayon posé
- Un tableau `char**` classique : un `malloc` pour les lignes, un par ligne pour les colonnes
- Le plateau est initialisé entièrement à `' '` (mort), jamais laissé indéterminé

---

## Étape 2 : libération mémoire (fonction générique)

```c
void free_board(char **board)
{
	if (board)
	{
		for (int i = 0; i < g_height; i++)
			if (board[i])
				free(board[i]);
		free(board);
	}
}
```

Explication :
- Paramétrée par `board` (pas figée sur `g_board`) pour être réutilisable sur n'importe
  quel tableau `height x width`, y compris le buffer temporaire de `play()`
- `g_height` reste global car la dimension ne change jamais après le parsing des arguments

---

## Étape 3 : lecture des commandes (`read_commands`)

```c
void read_commands(void)
{
	char buffer;
	int  valid;

	while (read(STDIN_FILENO, &buffer, 1) == 1)
	{
		valid = 1;
		if (buffer == 'w')
		{
			if (g_i > 0)
				g_i--;
		}
		else if (buffer == 's')
		{
			if (g_i < g_height - 1)
				g_i++;
		}
		else if (buffer == 'a')
		{
			if (g_j > 0)
				g_j--;
		}
		else if (buffer == 'd')
		{
			if (g_j < g_width - 1)
				g_j++;
		}
		else if (buffer == 'x')
			g_draw = !g_draw;
		else
			valid = 0;
		if (valid && g_draw)
			g_board[g_i][g_j] = 'O';
	}
}
```

Explication de la boucle :
- `valid` est réinitialisé à `1` **à chaque itération**, pas une seule fois avant la boucle
  — sinon un seul caractère invalide (le `\n` final d'`echo`) bloque tout marquage pour
  le reste de la lecture
- Aucun `return` dans le cas "caractère non reconnu" : on ignore juste ce caractère et
  la lecture de `stdin` continue normalement
- `x` marque la case courante **immédiatement**, au même titre qu'un déplacement — ce
  n'est pas un simple interrupteur silencieux
- Les bornes de `g_i`/`g_j` sont garanties par construction (`g_i > 0`, `g_i < g_height - 1`,
  etc.) : pas besoin de re-vérifier ces bornes plus loin dans le code, ce serait redondant

---

## Étape 4 : voisinage et génération suivante

```c
int count_neighbors(int i, int j)
{
	int count = 0;

	for (int di = -1; di <= 1; di++)
	{
		for (int dj = -1; dj <= 1; dj++)
		{
			if (di == 0 && dj == 0)
				continue;
			int ni = i + di;
			int nj = j + dj;
			if (ni >= 0 && ni < g_height && nj >= 0 && nj < g_width)
				if (g_board[ni][nj] == 'O')
					count++;
		}
	}
	return (count);
}

void compute_generation(char **next)
{
	for (int i = 0; i < g_height; i++)
	{
		for (int j = 0; j < g_width; j++)
		{
			int n = count_neighbors(i, j);
			if (g_board[i][j] == 'O')
				next[i][j] = (n == 2 || n == 3) ? 'O' : ' ';
			else
				next[i][j] = (n == 3) ? 'O' : ' ';
		}
	}
}
```

Explication de `count_neighbors()` :
- Parcourt les 8 cases autour de `(i, j)` (`di`/`dj` de `-1` à `1`, en sautant `(0,0)`)
- Une case hors plateau est simplement ignorée par le test `ni/nj` — elle compte comme morte,
  conformément au sujet (*"each cell outside of the array will be considered dead"*)

Explication de `compute_generation()` :
- Écrit la génération suivante dans `next`, jamais dans `g_board` directement
  (on ne modifie pas un tableau qu'on est en train de lire pour calculer ses voisins)
- Applique exactement les règles du tableau de la section précédente

---

## Étape 5 : `play()` — un seul buffer temporaire pour toutes les itérations

```c
int play(void)
{
	char **temp;

	if (g_iterations == 0)
		return (0);

	temp = (char **)malloc(sizeof(char *) * g_height);
	if (!temp)
		return (-1);
	for (int i = 0; i < g_height; i++)
	{
		temp[i] = (char *)malloc(sizeof(char) * g_width);
		if (!temp[i])
			return (-1);
	}

	for (int n = 0; n < g_iterations; n++)
	{
		compute_generation(temp);
		char **swap = g_board;
		g_board = temp;
		temp = swap;
	}

	free_board(temp);
	return (0);
}
```

Explication :
- `temp` est alloué **une seule fois**, avant la boucle sur `g_iterations`
- À chaque itération, on calcule la génération dans `temp` puis on **échange les pointeurs**
  `g_board` ↔ `temp` — aucun nouveau `malloc`/`free` à chaque génération
- Coût mémoire final : un seul buffer supplémentaire, quel que soit le nombre d'itérations
- `free_board(temp)` libère le buffer devenu inutile une fois la boucle terminée

---

## Étape 6 : affichage (`print_board`)

```c
void print_board(void)
{
	for (int i = 0; i < g_height; i++)
	{
		for (int j = 0; j < g_width; j++)
			putchar(g_board[i][j]);
		putchar('\n');
	}
}
```

Explication :
- `write` n'est **pas** dans la liste des fonctions autorisées — seul `putchar` peut servir
- Chaque ligne fait toujours exactement `g_width` caractères, espaces compris, y compris
  en début et fin de ligne

---

## Étape 7 : `main()` — l'orchestrateur

```c
int main(int argc, char *argv[])
{
	if (argc != 4)
		return (1);

	g_width = atoi(argv[1]);
	g_height = atoi(argv[2]);
	g_iterations = atoi(argv[3]);
	g_i = 0;
	g_j = 0;
	g_draw = 0;

	if (init_board() == -1)
	{
		free_board(g_board);
		return (1);
	}

	read_commands();

	if (play() == -1)
	{
		free_board(g_board);
		return (1);
	}

	print_board();
	free_board(g_board);

	return (0);
}
```

Explication :
- Parsing des arguments avec `atoi` uniquement, pas de validation supplémentaire demandée
- `g_i`, `g_j`, `g_draw` initialisés explicitement à `0` (le curseur démarre en haut à gauche,
  crayon levé)
- Chaque étape est appelée dans l'ordre du sujet : construire, dessiner, simuler, afficher

---

## Compilation

```bash
gcc -Wall -Wextra -Werror life.c -o life
echo 'sdxddssaaww' | ./life 5 5 0 | cat -e
```

Sortie attendue (conforme à l'exemple du sujet) :
```
$
OOO $
O O $
OOO $
$
```

---

## Si un `.h` est explicitement exigé par "Expected files"

Si le sujet impose *littéralement* `*.c *.h`, fournis un header minimal, sans prototype
si tu gardes tout dans `life.c` sans `#include` du header ailleurs :

```c
#ifndef LIFE_H
#define LIFE_H

#endif
```

Ça respecte la lettre de la consigne sans réintroduire de complexité.

---

## Résumé des règles importantes

| Règle | Application |
|---|---|
| `alive` = lettre `'O'`, jamais chiffre `'0'` | `read_commands()`, `compute_generation()` |
| `valid` réinitialisé à chaque tour de boucle | `read_commands()` |
| Pas de `return` sur caractère invalide | `read_commands()`, cas `else` |
| `x` marque la case courante immédiatement | `read_commands()`, cas `'x'` |
| Bornes déjà garanties par les `if` de déplacement | pas de re-check dans `read_commands()` |
| Cellule hors plateau = toujours morte | `count_neighbors()` |
| `write` interdit, seul `putchar` autorisé | `print_board()` |
| Un seul buffer temporaire pour toutes les itérations | `play()`, échange de pointeurs |
| Chaque ligne affichée fait exactement `width` caractères | `print_board()` |
