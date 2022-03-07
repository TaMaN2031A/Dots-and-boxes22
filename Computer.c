//function of computer move , select a random empty line
#include <stdlib.h>
#include <stdio.h>

void Computer(int *row, int *col, int size, char grid[][size], int d[][8], int moves)
{
    int i, j;

    for(i = 1; i < size; i++)
    {
        for(j = 1; j < size; j++)
        {
            if(i%2 == 0 && j%2 != 0 && grid[i][j] == 32)
            {
                grid[i][j] = 'V';
                *row = i;
                *col = j;
                d[moves][0] = i;
                d[moves][1] = j;
                return;
            }else if(i%2 != 0 && j%2 == 0 && grid[i][j] == 32)
            {
                grid[i][j] = 'H';
                *row = i;
                *col = j;
                d[moves][0] = i;
                d[moves][1] = j;
                return;
            }
        }
    }

}
