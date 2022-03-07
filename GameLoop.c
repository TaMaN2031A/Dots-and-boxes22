#include "HexaScan.h"
#include <stdio.h>
#include "Computer.h"
#include "printGame.h"
#include <stdlib.h>
#include "CheckBoxes.h"
#include <time.h>
#include <string.h>
#include "Struct.h"

//game loop function is the best and larger function in this project
//enjoy discovering it :)


void GameLoop(int size, char grid[][size],int len1, int len2, char name1[], char name2[], int score1, int score2, int Moves1, int Moves2, int mode, int TotalMoves, int GameDetails[][8], int MovesPlayed, int gamer, TOP top[10])
{

    time_t start;
    int t0 = time(&start);
    system("cls");
    fflush(stdin);
    int row, col;//numbers of row and col. the player choose
    int un = 0;//no. of undos
    int remaininglines = TotalMoves - MovesPlayed;//no. of remaining moves
    Game_Print(size, grid, name1, name2, score1, score2, Moves1, Moves2, remaininglines, t0);
    while(MovesPlayed < TotalMoves)//while game doesnot end
    {
        if(gamer == 2 && mode == 1)//if computer turn
        {
            Computer(&row, &col, size, grid, GameDetails, MovesPlayed);
            GameDetails[MovesPlayed][2] = 2;
            MovesPlayed++;
            Moves2++;
        }else
        {
            if(gamer == 1)//player 1 turn
            {
                blue();
            }else//player 2 turn
            {
                red();
            }
            printf("\n\n\t\t\tPlayer %d turn", gamer);
            //take row and col numbers
            printf("\n\n\t\t\tEnter row number : ");
            row = HexaScan();
            printf("\n\t\t\tEnter column number : ");
            col = HexaScan();
            while(row < 1 || row >= size || col < 1 || col >= size || (row == col && row > 4) || (row%2 == 0 && col%2 == 0 && row != col))//check validity of inputs
            {
                printf("\n\n\t\tInvalid inputs!");
                printf("\n\n\t\t\tEnter row number : ");
                row = HexaScan();
                printf("\n\t\t\tEnter column number : ");
                col = HexaScan();
            }
            reset();
            if(row == col)//special case to do special things
            {
                if(row == 1)//save the game and continue
                {
                    printf("Enter the file number( 1 or 2 or 3):");
                    int choice = 0;
                    int valid = 0;
                    while(valid != 1 || choice < 1 || choice > 3)//get no. of file he want to save to
                    {
                        printf("\n\n\t\t\tEnter the number of file : ");
                        valid = scanf("%d", &choice);
                        while(valid != 1)
                        {
                            printf("\n\tThis is invalid choice\n");
                            scanf("%*[^\n]");//copied from youtube
                            printf("\tPlease enter 1 or 2 or 3 : ");
                            valid = scanf("%d", &choice);
                        }
                    }
                    //save every thing which use as a parameter in game loop
                    char file[5];
                    sprintf(file, "%d.txt", choice);
                    FILE *save = fopen(file, "w");
                    fwrite(&size, sizeof(int), 1, save);
                    fwrite(grid, sizeof(char), size * size, save);
                    fwrite(&len1, sizeof(int), 1, save);
                    fwrite(&len2, sizeof(int), 1, save);
                    fwrite(name1, sizeof(char), len1, save);
                    fwrite(name2, sizeof(char), len2, save);
                    fwrite(&score1, sizeof(int), 1, save);
                    fwrite(&score2, sizeof(int), 1, save);
                    fwrite(&Moves1, sizeof(int), 1, save);
                    fwrite(&Moves2, sizeof(int), 1, save);
                    fwrite(&mode, sizeof(int), 1, save);
                    fwrite(&TotalMoves, sizeof(int), 1, save);
                    fwrite(GameDetails, sizeof(int), TotalMoves * 8, save);
                    fwrite(&MovesPlayed, sizeof(int), 1, save);
                    fwrite(&gamer, sizeof(int), 1, save);
                    fclose(save);
                    printf("saved to file %d\n", choice);
                    continue;
                }else if(row == 2)//undo
                {
                    if(MovesPlayed == 0)//if no moves played to undo
                    {
                        yellow();
                        printf("\n\t\t\tNo moves to undo");
                        reset();
                        continue;
                    }else{
                        if(mode == 1)//undo in vs computer mode we undo all computer moves and last move of the player
                        {
                            un++;
                            MovesPlayed--;
                            Moves1--;
                            int n1 = GameDetails[MovesPlayed-1][7];
                            int r1 = GameDetails[MovesPlayed][0];
                            int c1 = GameDetails[MovesPlayed][1];
                            int b1 = GameDetails[MovesPlayed-1][3];
                            int b2 = GameDetails[MovesPlayed-1][4];
                            int b3 = GameDetails[MovesPlayed-1][5];
                            int b4 = GameDetails[MovesPlayed-1][6];
                            int g = GameDetails[MovesPlayed][2];
                            if(g == 1)//if the previous turn is a player's turn that's meaning the player closed a box or chain then we'll delete the line he choosed and boxes he closed
                            {
                                b1 = GameDetails[MovesPlayed][3];
                                b2 = GameDetails[MovesPlayed][4];
                                b3 = GameDetails[MovesPlayed][5];
                                b4 = GameDetails[MovesPlayed][6];
                                grid[r1][c1] = 32;//delet the line
                                //check if he close one box or chain
                                if(b1 == 0 && b3 != 0)//one box
                                {
                                    b3 = GameDetails[MovesPlayed][5];
                                    b4 = GameDetails[MovesPlayed][6];
                                    grid[b3][b4] = 32;
                                    score1--;
                                }else if(b1 != 0 && b3 == 0)//one box
                                {
                                    b1 = GameDetails[MovesPlayed][3];
                                    b2 = GameDetails[MovesPlayed][4];
                                    grid[b1][b2] = 32;
                                    score1--;
                                }else if(b1 != 0 && b3 != 0)//chain(two boxes)
                                {
                                    b1 = GameDetails[MovesPlayed][3];
                                    b2 = GameDetails[MovesPlayed][4];
                                    grid[b1][b2] = 32;
                                    b3 = GameDetails[MovesPlayed][5];
                                    b4 = GameDetails[MovesPlayed][6];
                                    grid[b3][b4] = 32;
                                    score1 -= 2;
                                }

                            }else if(b1 == 0 && b3 == 0)//if the previous turn is computer's turn and no closed boxes
                            {
                                Moves2--;
                                grid[r1][c1] = 32;
                                MovesPlayed--;
                                r1 = GameDetails[MovesPlayed][0];
                                c1 = GameDetails[MovesPlayed][1];
                                grid[r1][c1] = 32;
                            }else if(b1 != 0 || b3 != 0)//if the previous turn is computer's turn and box or chain was closed by the computer
                            {
                                Moves2 = Moves2-(n1+1);
                                grid[r1][c1] = 32;
                                for(int i = 0; i <= n1; i++)//remove all plays of the computer in a row
                                {
                                    MovesPlayed--;
                                    r1 = GameDetails[MovesPlayed][0];
                                    c1 = GameDetails[MovesPlayed][1];
                                    b1 = GameDetails[MovesPlayed][3];
                                    b2 = GameDetails[MovesPlayed][4];
                                    b3 = GameDetails[MovesPlayed][5];
                                    b4 = GameDetails[MovesPlayed][6];
                                    grid[r1][c1] = 32;
                                    if(b1 == 0 && b3 != 0)//if one box closed
                                    {
                                        b3 = GameDetails[MovesPlayed][5];
                                        b4 = GameDetails[MovesPlayed][6];
                                        grid[b3][b4] = 32;
                                        score2--;
                                    }else if(b1 != 0 && b3 == 0)//if one box closed
                                    {
                                        b1 = GameDetails[MovesPlayed][3];
                                        b2 = GameDetails[MovesPlayed][4];
                                        grid[b1][b2] = 32;
                                        score2--;
                                    }else if(b1 != 0 && b3 != 0)//if chain closed
                                    {
                                        b1 = GameDetails[MovesPlayed][3];
                                        b2 = GameDetails[MovesPlayed][4];
                                        grid[b1][b2] = 32;
                                        b3 = GameDetails[MovesPlayed][5];
                                        b4 = GameDetails[MovesPlayed][6];
                                        grid[b3][b4] = 32;
                                        score2 -= 2;
                                    }
                                }

                            }
                            system("cls");
                            remaininglines = TotalMoves - MovesPlayed;
                            Game_Print(size, grid, name1, name2, score1, score2, Moves1, Moves2, remaininglines, t0);
                            continue;
                        }else{//if vs player mode we'll delete the last move only
                           un++;
                           MovesPlayed--;
                           int R = GameDetails[MovesPlayed][0];
                           int C = GameDetails[MovesPlayed][1];
                           gamer = GameDetails[MovesPlayed][2];//change the turn to the previous one
                           grid[R][C] = 32;//delete the line
                           int b1 = GameDetails[MovesPlayed][3];
                           int b2 = GameDetails[MovesPlayed][4];
                           int b3 = GameDetails[MovesPlayed][5];
                           int b4 = GameDetails[MovesPlayed][6];
                           if(gamer == 1)
                           {
                               Moves1--;
                           }else{
                               Moves2--;
                           }
                           //check if a box was closed or chain
                           if(b1 != 0 || b3 != 0 )
                           {
                               if(b1 == 0 && b3 != 0)//if one box
                               {
                                   grid[b3][b4] = 32;
                                   if(gamer == 1)
                                   {
                                       score1--;
                                   }else{
                                       score2--;
                                   }
                               }else if(b1 != 0 && b3 == 0)//if one box
                               {
                                   grid[b1][b2] = 32;
                                   if(gamer == 1)
                                   {
                                       score1--;
                                   }else{
                                       score2--;
                                   }
                               }else if(b1 != 0 && b3 != 0)//if a chain
                               {
                                   grid[b1][b2] = 32;
                                   grid[b3][b4] = 32;
                                   if(gamer == 1)
                                   {
                                       score1 -= 2;
                                   }else{
                                       score2 -= 2;
                                   }
                               }
                           }
                           system("cls");
                           remaininglines = TotalMoves - MovesPlayed;

                           Game_Print(size, grid, name1, name2, score1, score2, Moves1, Moves2, remaininglines, t0);
                           continue;
                        }
                    }
                }else if(row == 3)//redo
                {
                    if(un == 0)//if there is no undos then there is no moves to redo
                    {
                        yellow();
                        printf("\n\t\t\tNo moves to redo!");
                        reset();
                        continue;
                    }else{
                        if(mode == 1)//redo in vs computer mode we redo the player move and the computer will redo its moves automatically
                        {
                            un--;

                            int r1 = GameDetails[MovesPlayed][0];
                            int c1 = GameDetails[MovesPlayed][1];
                            int b1 = GameDetails[MovesPlayed][3];
                            int b2 = GameDetails[MovesPlayed][4];
                            int b3 = GameDetails[MovesPlayed][5];
                            int b4 = GameDetails[MovesPlayed][6];
                            MovesPlayed++;
                            if(r1%2 == 0 && c1%2 != 0)//if vertical line
                            {
                              Moves1++;
                              grid[r1][c1] = 'v';
                            }
                            else if(r1%2 != 0 && c1%2 == 0)//if horizontal line
                            {
                              grid[r1][c1] = 'h';
                              Moves1++;
                            }
                            //check boxes
                            if(b1 != 0 || b3 != 0)
                            {
                                if(b1 == 0 && b3 != 0)
                                {
                                    grid[b3][b4] = 'A';
                                    score1++;
                                }
                                else if(b1 != 0 && b2 == 0)
                                {
                                    grid[b1][b2] = 'A';
                                    score1++;
                                }
                                else if(b1 != 0 && b2 != 0)
                                {
                                  grid[b1][b2] = 'A';
                                  grid[b3][b4] = 'A';
                                  score1 += 2;
                                }
                            }
                            if(GameDetails[MovesPlayed][2] == 2)//if computer's turn we won't print to reduce time
                            {
                                gamer = 2;
                            }
                            if(gamer == 2) continue;
                           system("cls");
                           remaininglines = TotalMoves - MovesPlayed;
                           Game_Print(size, grid, name1, name2, score1, score2, Moves1, Moves2, remaininglines, t0);
                           continue;
                        }else{//redo in vs player mode we will redo the previous move
                        un--;
                        int r1 = GameDetails[MovesPlayed][0];
                        int c1 = GameDetails[MovesPlayed][1];
                        int g = GameDetails[MovesPlayed][2];//check who's turn
                        int b1 = GameDetails[MovesPlayed][3];
                        int b2 = GameDetails[MovesPlayed][4];
                        int b3 = GameDetails[MovesPlayed][5];
                        int b4 = GameDetails[MovesPlayed][6];
                        MovesPlayed++;
                        if(r1%2 == 0 && c1%2 != 0)//if vertical line
                        {
                           if(g == 1)//if player one
                           {
                               Moves1++;
                               grid[r1][c1] = 'v';
                           }else{//if player 2
                              grid[r1][c1] = 'V';
                              Moves2++;
                           }
                        }else if(r1%2 != 0 && c1%2 == 0)//if horizontal line
                        {
                           if(g == 1)
                           {
                              grid[r1][c1] = 'h';
                              Moves1++;
                           }else{
                              grid[r1][c1] = 'H';
                              Moves2++;
                           }
                        }
                        if(b1 != 0 || b3 != 0)//check boxes
                        {
                            if(b1 == 0 && b3 != 0)//if one box
                            {
                                if(g == 1)
                                {
                                    score1++;
                                    grid[b3][b4] = 'A';
                                }else{
                                    score2++;
                                    grid[b3][b4] = 'B';
                                }
                            }else if(b1 != 0 && b3 == 0)//if one box
                            {
                                if(g == 1)
                                {
                                    score1++;
                                    grid[b1][b2] = 'A';
                                }else{
                                    score2++;
                                    grid[b1][b2] = 'B';
                                }
                            }else if(b1 != 0 && b3 != 0)//if chain
                            {
                                if(g == 1)
                                {
                                    score1 += 2;
                                    grid[b3][b4] = 'A';
                                    grid[b1][b2] = 'A';
                                }else{
                                    score2 += 2;
                                    grid[b3][b4] = 'B';
                                    grid[b1][b2] = 'B';
                                }
                            }
                        }
                    }
                        system("cls");
                        remaininglines = TotalMoves - MovesPlayed;
                        Game_Print(size, grid, name1, name2, score1, score2, Moves1, Moves2, remaininglines, t0);
                        continue;
                    }
                }else if(row == 4)//back to main menu
                {
                    system("cls");
                    main();
                    return;
                }
            }else{//if a normal move
                if(grid[row][col] == 32)//check if the move is valid
                {
                   un = 0;//to stop redo
                   //record the move in MovesPlayed array
                   GameDetails[MovesPlayed][0] = row;
                   GameDetails[MovesPlayed][1] = col;
                   GameDetails[MovesPlayed][2] = gamer;
                   MovesPlayed++;
                   if(gamer == 1)
                   {
                       Moves1++;
                   }else{
                       Moves2++;
                   }
                   if(row%2 == 0 && col%2 != 0)//if vertical
                   {
                       if(gamer == 1)
                       {
                           grid[row][col] = 'v';
                       }else{
                           grid[row][col] = 'V';
                       }
                   }else if(row%2 != 0 && col%2 == 0)//if horizontal
                   {
                       if(gamer == 1)
                       {
                           grid[row][col] = 'h';
                       }else{
                           grid[row][col] = 'H';
                       }
                   }
                }else{//if invalid move
                    printf("\n\t\t\tInvalid inputs!");
                    continue;
                }
            }
        }
        int Box = 0;
        Box = checkbox(row, col, size, grid, gamer, MovesPlayed, GameDetails);//check if box or chain was closed
        if(Box == 0)//if no boxes closed then change the player
        {
            if(gamer == 1)
            {
                gamer = 2;
            }else
            {
                gamer = 1;
            }
        }else//if box or chain was closed
        {
            if(gamer == 1)
            {
                score1 += Box;
            }else
            {
                if(mode == 1)//if computer turn we will record that in GameDetails array to make undo and redo
                {
                    int n = GameDetails[MovesPlayed-2][7];
                    GameDetails[MovesPlayed-1][7] = n + 1;
                }
                score2 += Box;
            }
        }
        if(gamer == 2 && mode == 1)//if computer turn we don't print the game
        {
            continue;
        }
        system("cls");
        remaininglines = TotalMoves - MovesPlayed;
        Game_Print(size, grid, name1, name2, score1, score2, Moves1, Moves2, remaininglines, t0);

    }
    //loop end which meaning the game end
    printf("\n\n\t\t\tGame End");
    int Winner, found = 1;
    //check who is the winner
    if(score1 > score2)//player one won
    {
        Winner = 1;
        blue();
        printf("\n\n\t\t\t%s is the WINNER", name1);
    }else if(score2 > score1)//player two won
    {
        Winner = 2;
        red();
        printf("\n\n\t\t\t%s is the WINNER", name2);
    }else if(score1 == score2)//no winner :(
    {
        Winner = 0;
        yellow();
        printf("\n\n\t\t\tTIE (no winner)");
    }
    //record the winner in top10 list
    if(Winner == 1)
    {
        for(int i  = 0; i < 10; i++)
        {
            if(top[i].len != 0)
            {

                if(!strcmp((const)top[i].name, (const)name1))//check if he exist in the list
                {
                    found = 0;
                    if(top[i].score < score1)//if the new score is larger than the old one
                    {
                        top[i].score = score1;//record the new(higher) score
                    }
                    break;
                }
            }
        }
        if(found)//if he doesn't exist in the list
        {
            if(score1 > top[9].score)//if his score larger than the last one in the list
            {
                //record his informations in the list
                top[9].score = score1;
                top[9].len = len1;
                strcpy(top[9].name, name1);
            }
        }
    }else if(Winner == 2 && mode == 2)//if computer won we don't record it
    {
        //we do the same thing with player two as previous
        for(int i  = 0; i < 10; i++)
        {
            if(top[i].len != 0)
            {

                if(!strcmp((const)top[i].name, (const)name2))
                {
                    found = 0;
                    if(top[i].score < score2)
                    {
                        top[i].score = score2;
                    }
                    break;
                }
            }
        }
        if(found)
        {
            if(score2 > top[9].score)
            {
                top[9].score = score2;
                top[9].len = len2;
                strcpy(top[9].name, name2);
            }
        }
    }
    //save the list in a text file
    FILE *leader = fopen("T.txt", "w");
            int c = 0;
            while(c < 10)
            {
                fwrite(&top[c].len, sizeof(int), 1, leader);
                fwrite(top[c].name, sizeof(char), top[c].len, leader);
                fwrite(&top[c].score, sizeof(int), 1, leader);
                c++;
            }
    fclose(leader);
    reset();
    green();
    //take a choice from player
    printf("\n\n\t\t\tPlay again(enter : 1)"
           "\n\n\t\t\tBack to main menu(enter : 2)"
           "\n\n\t\t\tExit(enter : 3)");
   int choice = 0;
   int valid = 0;

   while(valid != 1 || choice < 1 || choice > 3)
   {
        printf("\n\n\t\t\tEnter the number of your choice : ");
        valid = scanf("%d", &choice);
        while(valid != 1)
        {
            printf("\n\tThis is invalid choice\n");
            scanf("%*[^\n]");//copied from youtube
            printf("\tPlease enter 1 or 2 or 3 : ");
            valid = scanf("%d", &choice);

        }
   }
   switch(choice)
   {
   case 1 :
    system("cls");
    play(top);//play again
    return;
   case 2 :
    system("cls");
    main();//back to main menu
    return;
   case 3 :
    return;//close the game

   }
}

