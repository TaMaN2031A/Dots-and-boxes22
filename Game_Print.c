//function to print the game
#include <time.h>

void Game_Print(int size, char grid[][size], char name1[], char name2[], int score1, int score2, int moves1, int moves2, int remaining, int t0)
{
    //calculate the time passed in minutes and seconds
    time_t end;
    int t1 = time(&end);
    int S = (t1 - t0) % 60, M = (t1 - t0) / 60;
    char horizontal = 205, vertical = 186, dot = 254;
    int i, j;
    printf("\n\n\n\n\t\t\t\t  ");
    for(i = 1; i < size; i++)//print the first line(hexadecimal numbers)
    {
        if(i < 16)
        {
            printf("%x ", grid[i][0]);

        }else if(i == 16){//in case of 8*8 boxes grid
            printf("g ");
        }else if(i == 17){
            printf("h");
        }
    }

        for(i = 1; i < size; i++)//print the grid
        {
            //print row number
            if(i < 16)
            {
                printf("\n\t\t\t\t%x ", grid[0][i]);
            }else if(i == 16)
            {
                printf("\n\t\t\t\tg ");
            }else if(i == 17)
            {
                printf("\n\t\t\t\th ");
            }
            for(j = 1; j < size; j++)
            {
                //print lines, dots and boxes
                if(grid[i][j] == 'v')//vertical line for player one
                {
                    blue();
                    printf("%c ", vertical);
                    reset();
                }else if(grid[i][j] == 'h')//horizontal line for player one
                {
                    blue();
                    printf("%c%c%c", horizontal, horizontal, horizontal);
                    reset();
                }else if(grid[i][j] == 'V')//vertical line for player two
                {
                    red();
                    printf("%c ", vertical);
                    reset();
                }else if(grid[i][j] == 'H')//horizontal line for player two
                {
                    red();
                    printf("%c%c%c", horizontal, horizontal, horizontal);
                    reset();
                }else if(grid[i][j] == 'A')//box for player one
                {
                    blue();
                    printf("%c ", grid[i][j]);
                    reset();
                }else if(grid[i][j] == 'B')//box for player two
                {
                    red();
                    printf("%c ", grid[i][j]);
                    reset();
                }else{//dot or empty element
                    reset();
                    if(i%2 != 0 && j%2 == 0)//empty horizontal line
                    {
                        printf("%c%c%c", grid[i][j], grid[i][j], grid[i][j]);
                    }else if(i%2 != 0 && j%2 != 0)//dot
                    {
                        printf("%c", grid[i][j]);
                    }else{//empty box
                        printf("%c ", grid[i][j]);
                    }
                }
            }
        }
        //print game details(names, scores, no. of moves,....etc)
    blue();
    printf("\n\nPlayer one name : %s", name1);
    red();
    printf("\t\t\t\tPlayer two name : %s", name2);
    blue();
    printf("\nPlayer one score : %d", score1);
    red();
    printf("\t\t\t\tPlayer two score : %d", score2);
    blue();
    printf("\nPlayer one moves : %d", moves1);
    red();
    printf("\t\t\t\tPlayer two moves : %d", moves2);
    green();
    printf("\n\nNo. of ramaining lines : %d", remaining);

    cyan();
    printf("\t\t\t\tTime %.1d : %.1d", M, S);
    green();
    printf("\n\n\t\t\tSave Game(enter : 1, 1)"
           "\n\t\t\tUndo(enter : 2, 2)"
           "\n\t\t\tRedo(enter : 3, 3)"
           "\n\t\t\tBack to main menu(enter : 4, 4)");
    reset();
    return;
}


