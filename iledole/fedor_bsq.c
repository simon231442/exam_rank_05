/*
 * on s'en fout des \n
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct t_map
{
    int col;
    int row;
    char obstacle;
    char space;
    char full;
    char **map;
} t_map;

int is_printable(char c)
{
    if (c >= ' ' && c <= '~')
    {
        return (0);
    }
    return (1);
}

int check_map(FILE *fd, t_map *map)
{
    if (fscanf(fd, "%d %c %c %c", &map->row, &map->space, &map->obstacle, &map->full) != 4) // rajoute \n
        return (1);
    printf("%d\n", map->row);
    if (map->row < 1)
        return (1);
    if (fgetc(fd) != '\n')
        return (1);
    
    if (is_printable(map->full) == 1)
        return (1);
    if (is_printable(map->obstacle) == 1)
        return (1);
    if (is_printable(map->space) == 1)
        return (1);
    return (0);
}

int parse_map(FILE *fd, t_map *map)
{
    char *line = NULL;
    size_t cap = 0;
    int taille = 0;

    map->map = calloc(map->row + 1, sizeof(char *));
    if (map->map == NULL)
    {
        map->map = NULL;
        return (1);
    }

    int i = 0;
        
    while (i < map->row)
    {
        printf("dans boucle\n");
        line = NULL;
        cap = 0;

        taille = (int)getline(&line, &cap, fd);
        if (taille < 0)
            return (1);
//
        if (i == 0)
            map->col = taille;//fct qui compte la taille sans le \n
        else if (taille != map->col)
        {
            printf("taille ne st pas bonne\n");
            return (1);
        }
        map->map[i] = line;//substring qui prend line de getline sans \n

        if (line[taille - 1] != '\n')//encore en s'en tape du \n
        {
            printf("line n est pas bonne\n");
            return (1);
        }
        map->map[i][taille - 1] = '\0';
//
        int c = 0;
        while (c < taille)
        {
            if (map->map[i][c] != map->space && map->map[i][c] != map->obstacle && map->map[i][c] != '\0')
            {
                /*printf("-------------------------------------------\n");
                printf("ligne : %s\n", map->map[i]);
                printf("charactere pas bon\n");
                printf("i : %d, c : %d\n", i, c);
                printf("%c\n", map->map[i][c]);
                printf("-------------------------------------------\n");*/
                return (1);
            }
            c++;
        }

        i++;
    }
    map->map[i] = NULL;
    return (0);
}

int min3(int a, int i, int c)
{
    if (a < i)
        i = a;
    if (c < i)
        i = c;
    return (i);
}

int solve(t_map *map)
{
    int *dp = calloc(map->col, sizeof(int));
    if (dp == NULL)
        return (1);

    int i = 0;
    int c = 0;

    int best = 0;
    int best_i = 0;
    int best_c = 0;

    int saved = 0;
    int up_left = 0;

    while (i != map->row)
    {
        c = 0;
        while (c != map->col)
        {
            saved = dp[c];
            if (map->map[i][c] != map->space)
                dp[c] = 0;
            else if (i == 0 || c == 0)
                dp[c] = 1;
            else
                dp[c] = min3(dp[c], dp[c - 1], up_left) + 1;
            up_left = saved;
            if (dp[c] > best)
            {
                best = dp[c];
                best_i = i;
                best_c = c;
            }
            c++;
        }
        i++;
    }
    i = best_i - best + 1;
    c = best_c - best + 1;

    while (i <= best_i)
    {
        c = best_c - best + 1;
        while (c <= best_c)
        {
            map->map[i][c] = map->full;
            c++;
        }
        i++;
    }



    free(dp);
    return (0);
}

int handle_map(FILE *fd)
{
    t_map map;
    
    if (check_map(fd, &map) == 1)
    {
        printf("dans le 1\n");
        return (1);
    }
    if (parse_map(fd, &map) == 1)
    {
        printf("dans le 2\n");
        return (1);
    }
    if (solve(&map) == 1)
    {
        return (1);
    }
    int i = 0;
    while (map.map[i] != NULL)
    {
        fprintf(stdout, "%s\n", map.map[i]);
        i++;
    }
    return (0);
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        FILE *fd = stdin;
        if (handle_map(fd) == 1)
        {
            fclose (fd);
            fprintf(stdout, "map error\n");
            return (0);
        }
        return (0);
    }
    else
    {
        FILE *fd = fopen(argv[1], "r");
        if (fd == NULL)
            return (0);
        if (handle_map(fd) == 1)
        {
            fclose (fd);
            fprintf(stdout, "map error\n");
            return (0);
        }
    }
}
