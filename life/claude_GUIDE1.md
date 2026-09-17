# GUIDE — `life` en une seule version simplifiée (sans `.h`, sans `struct`, variables globales)

Ce guide propose une version alternative de l'exercice, pensée pour l'examen chronométré :
**un seul fichier `.c`**, **aucune structure**, **variables globales** à la place de `t_game`.
L'objectif : réduire le nombre de choses à taper et à relire sous pression, tout en gardant
un code strictement conforme au sujet.

> ⚠️ Vérifie toujours si ton sujet exact impose `*.c *.h`. Si un `.h` est explicitement exigé
> dans "Expected files", il faudra quand même fournir un header minimal (même presque vide)
> pour respecter la consigne — voir la section finale à ce sujet.

---

## 1. Rappel des règles (à connaître par cœur, elles ne sont jamais explicitées dans le sujet)

Le sujet dit juste *"simulate a game of life"* — c'est une référence au jeu de Conway (1970),
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

## 2. Rappel du prototype et des contraintes

```
./life width height iterations
```

- Fonctions autorisées : `atoi`, `read`, `putchar`, `malloc`, `calloc`, `realloc`, `free`
  → **pas de `write`**, pas de `printf`. L'affichage se fait avec `putchar`.
- Un curseur ("crayon") démarre en `(0, 0)`.
- Commandes lues sur `stdin` : `w a s d` déplacent, `x` bascule le mode dessin.
- Cellule vivante → `'O'` (lettre majuscule, **pas** le chiffre `'0'`).
- Cellule morte → `' '` (espace).
- Chaque ligne affichée fait toujours exactement `width` caractères, espaces compris.

---

## 3. Pourquoi des variables globales plutôt qu'une `struct` ?

Avantages en contexte d'examen :
- Pas de `t_game*` à passer et déréférencer partout (`game->i` devient juste `i`)
- Pas de `.h` à synchroniser avec le `.c`
- Moins de frappe = moins de fautes de frappe sous pression

Inconvénients (à connaître, mais acceptables pour un exercice de cette taille) :
- Moins "propre" au sens génie logiciel (état global mutable)
- Ne passerait pas la norme officielle 42 en dehors d'un examen chronométré
- Plus risqué sur un projet plus gros — mais `life` est un petit programme autonome

---

## 4. Le code complet (`life.c`, un seul fichier)

```c
#include <stdlib.h>
#include <unistd.h>

/* ---- Variables globales : remplacent t_game ---- */
int   g_width;
int   g_height;
int   g_iterations;
int   g_i;          /* position courante du curseur (ligne)   */
int   g_j;          /* position courante du curseur (colonne) */
int   g_draw;        /* mode dessin : 0 = off, 1 = on */
char  **g_board;

/* ---- Allocation d'un plateau vide (width x height), rempli d'espaces ---- */
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

/* ---- Libère un plateau quelconque (réutilisable pour g_board ou un buffer temporaire) ---- */
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

/* ---- Lecture des commandes de dessin sur stdin ---- */
void read_commands(void)
{
	char buffer;
	int  valid;

	while (read(STDIN_FILENO, &buffer, 1) == 1)
	{
		valid = 1;   /* réinitialisé À CHAQUE itération : voir section 5 */
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

/* ---- Compte les voisines vivantes de la cellule (i, j) ---- */
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

/* ---- Calcule une génération et l'écrit dans "next" (déjà alloué) ---- */
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

/* ---- Joue toutes les itérations avec un seul buffer temporaire (voir section 6) ---- */
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
		/* échange des pointeurs : aucun nouveau malloc nécessaire */
		char **swap = g_board;
		g_board = temp;
		temp = swap;
	}

	free_board(temp);   /* libère le buffer devenu inutile */
	return (0);
}

/* ---- Affichage final avec putchar uniquement (write n'est pas autorisé) ---- */
void print_board(void)
{
	for (int i = 0; i < g_height; i++)
	{
		for (int j = 0; j < g_width; j++)
			putchar(g_board[i][j]);
		putchar('\n');
	}
}

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

---

## 5. Points de vigilance repris de nos échanges précédents

Ces bugs ont été identifiés en analysant plusieurs versions candidates — ils sont **corrigés**
dans le code ci-dessus, mais voici pourquoi ils comptent :

1. **`valid` doit être réinitialisé à chaque tour de boucle**, pas déclaré une seule fois avant
   la boucle — sinon, un seul caractère invalide (le `\n` final d'`echo`, par exemple) bloque
   silencieusement tout marquage de case pour le reste de la lecture.
2. **Jamais de `return` dans le cas "caractère invalide"** — la lecture de `stdin` doit continuer
   normalement après un caractère non reconnu, la commande suivante doit être traitée.
3. **`x` marque la case courante immédiatement**, au même titre qu'un déplacement — ce n'est pas
   un simple interrupteur silencieux.
4. **`alive` doit être `'O'`** (lettre), jamais `'0'` (chiffre) — sinon toute correspondance avec
   la moulinette échoue.
5. **Les bornes `i`/`j` sont déjà garanties par les conditions dans `read_commands`** (`i > 0`,
   `i < height - 1`, etc.) — donc pas besoin de re-vérifier ces bornes ailleurs dans le code,
   c'est redondant (voir section 3 de notre échange précédent).
6. **`write` n'est pas dans la liste des fonctions autorisées** — seul `putchar` peut servir à
   l'affichage final.

---

## 6. Pourquoi le buffer temporaire n'est alloué qu'une seule fois

Plutôt que `malloc`/`free` un tableau `temp` complet à *chaque* itération (`iterations` fois),
`play()` alloue `temp` **une seule fois avant la boucle**, puis échange simplement les pointeurs
`g_board` ↔ `temp` à chaque génération. Coût mémoire : un seul buffer supplémentaire, peu importe
le nombre d'itérations demandé.

---

## 7. Compilation et test

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

## 8. Si un `.h` est explicitement exigé par "Expected files"

Si le sujet impose *littéralement* `*.c *.h`, la moulinette peut s'attendre à trouver au moins
un fichier `.h` dans le rendu (même sans y mettre de prototypes). Dans ce cas, le plus simple :

```c
/* life.h — minimal, aucun prototype nécessaire si tout reste dans life.c */
#ifndef LIFE_H
#define LIFE_H

#endif
```

Ça respecte la lettre de la consigne ("fournir un `.h`") sans réintroduire de complexité —
tu n'es pas obligé d'y mettre les prototypes des fonctions si tu gardes tout en un seul `.c`
sans `#include` du header ailleurs.

**Recommandation** : si tu as le moindre doute sur cette exigence, garde une version avec `.h`
minimal prête, et utilise la version 100% `.c` uniquement si le sujet ne mentionne aucun fichier
attendu ou si "Expected files" n'est pas strictement vérifié par la moulinette.
