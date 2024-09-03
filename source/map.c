/* A bogus map for Jasmin to work with

1 1 1 1 1
1 0 0 0 1
1 0 N 0 1
1 0 0 0 1
1 1 1 1 1

*/


#define SQUARE_SIZE 5
#define	MIN 0
#define	MAX 4

#include <stdio.h>
#include <stdlib.h>

char **generate_bogus_map(void)
{
    char **map;
    int		y;
    int		x;

    map = malloc(sizeof(char *) * SQUARE_SIZE);
    y = -1;
    while (++y < SQUARE_SIZE)
    {
        map[y] = malloc(sizeof(char) * SQUARE_SIZE);
        x = -1;
        while (++x < SQUARE_SIZE)
        {
            /*if top or bottom row of the map,
            or leftmost or rightmost, set to wall*/
            if (y == MIN || y == MAX || x == MIN || x == MAX)
                map[y][x] = '1';
            else
                map[y][x] = '0';
        }
    }
    /*overwrite for player position in the center*/
    map[MAX / 2][MAX / 2] = 'E';
    return (map);
}

int main(void)
{
    int i;
    int j;
    char    **map;

    map = generate_bogus_map();
    i = -1;
    while (++i < SQUARE_SIZE)
    {
        j = -1;
        while (++j <= SQUARE_SIZE)
        {
            if (j < SQUARE_SIZE)
                printf("%c ", map[i][j]);
            else if (j == SQUARE_SIZE)
            {
                printf("\n");
                free(map[i]);
            }
        }
    }
    free(map);
}