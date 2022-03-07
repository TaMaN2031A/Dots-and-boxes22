#define SIZE 20
#include "printArrays.h"
#include <string.h>
#include <stdio.h>
#include "Game.h"
#include <time.h>
#include "Struct.h"



void StartNewGame();



void play(TOP top[])//take user choice if he want to start a new game or load a saved game
{
    green();
    int valid = 0, choice = 0;
    printf("\n\n\t\tNew Game(enter : 1)"
           "\n\n\t\tLoad Game(enter : 2)\n\n"
           "\t\tBack to main menu(enter : 3)\n\n");

    while(valid != 1 || choice > 3 || choice < 1)
   {
        printf("\t\tEnter the number of your choice : ");
        valid = scanf("%d", &choice);
        while(valid != 1)
        {
            printf("\n\tThis is invalid choice\n");
            scanf("%*[^\n]");//copied from youtube
            printf("\tPlease enter 1 or 2 or 3 : ");
            valid = scanf("%d", &choice);

        }
   }
   reset();

   switch(choice)
   {
   case 1 :
    system("cls");
    StartNewGame(top);
    break;
    return;
   case 2 :
      //load saved game
            green();
            printf("Enter the file number( 1 or 2 or 3):");
            int valid = 0, choice = 0;
            while(valid != 1 || choice > 3 || choice < 1)//take the file number he want to load
            {
                printf("\t\tEnter the number of your choice : ");
                valid = scanf("%d", &choice);
                while(valid != 1)
                {
                    printf("\n\tThis is invalid choice\n");
                    scanf("%*[^\n]");//copied from youtube
                    printf("\tPlease enter 1 or 2 or 3 : ");
                    valid = scanf("%d", &choice);
                }
            }
            reset();
                system("cls");
                char file[5];
                sprintf(file, "%d.txt", choice);
                FILE *load = fopen(file, "r");
                if(load == NULL)
                {
                    printf("file does not exist\n");
                }
                else//if the file exists
                {

                    //if the file is empty
                    fseek (load, 0, SEEK_END);
                    int fsize = ftell(load);
                    if (fsize == 0)
                    {
                        fclose(load);
                        yellow();
                        printf("file is empty\npress enter to back to the main menu\n");
                        reset();
                        char back;
                        scanf("%c", &back);
                        main();
                    }
                    else
                    {
                        fclose(load);
                        load = fopen(file, "r");
                    }
                    //load the game
                    int size, len1, len2, score1, score2, Moves1, Moves2, mode, TotalMoves, MovesPlayed, gamer;
                    char name1[100], name2[100];
                    fread(&size, sizeof(int), 1, load);
                    char grid[size][size];
                    fread(grid, sizeof(char), size * size, load);
                    fread(&len1, sizeof(int), 1, load);
                    fread(&len2, sizeof(int), 1, load);
                    fread(name1, sizeof(char), len1, load);
                    name1[len1] = '\0';
                    fread(name2, sizeof(char), len2, load);
                    name2[len2] = '\0';
                    fread(&score1, sizeof(int), 1, load);
                    fread(&score2, sizeof(int), 1, load);
                    fread(&Moves1, sizeof(int), 1, load);
                    fread(&Moves2, sizeof(int), 1, load);
                    fread(&mode, sizeof(int), 1, load);
                    fread(&TotalMoves, sizeof(int), 1, load);
                    int GameDetails[TotalMoves][8];
                    fread(GameDetails, sizeof(int), TotalMoves * 8, load);
                    fread(&MovesPlayed, sizeof(int), 1, load);
                    fread(&gamer, sizeof(int), 1, load);
                    fclose(load);
                    GameLoop(size, grid, len1, len2, name1, name2, score1, score2, Moves1, Moves2, mode, TotalMoves, GameDetails, MovesPlayed, gamer, top);
               }

   case 3 :
    system("cls");
    main();//back to main menu
    return;
   }

}

void StartNewGame(TOP top[])//function to initialize a new game
{
    green();
    printf("\n\n\t\tChoose mode :-"
          "\n\n\t\tOne player mode(enter : 1)"
          "\n\n\t\tTwo players mode(enter : 2)"
          "\n\n\n\n\t\tBack(enter : 3)"
          "\n\n\t\tBack to main menu(enter : 4)\n\n");
          int mode, Choice = 0, Valid = 0;
    while(Valid != 1 || Choice > 4 || Choice < 1)//get mode (1 or 2 players
   {
        printf("\t\tEnter the number of your choice : ");
        Valid = scanf("%d", &Choice);
        while(Valid != 1)
        {
            printf("\n\tThis is invalid choice\n");
            scanf("%*[^\n]");//copied from youtube
            printf("\tPlease enter 1 or 2 or 3 or 4 : ");
            Valid = scanf("%d", &Choice);

        }
   }
   reset();
   system("cls");
   if(Choice == 1)//vs computer
   {
       mode = 1;
   }else if(Choice == 2)//vs player
   {
       mode = 2;
   }else if(Choice == 3)
   {
       system("cls");
       play(top);//back to play menu
       return;
   }else if(Choice == 4)
   {
       system("cls");
       main();//back to main menu
       return;
   }
   player ONE, TWO;//tow structures contain name, namelength and no. of moves
   blue();
   printf("\n\n\t\tEnter player one name : ");
   fflush(stdin);
   gets(ONE.name);//get player one's name
   //intialize values
   ONE.score = 0;
   ONE.NoOfMoves = 0;
   TWO.score = 0;
   TWO.NoOfMoves = 0;
   if(mode == 1)//1 player mode
   {
       strcpy(TWO.name, "Computer");//set the player 2 name "Computer"
   }else//2 players mode
   {
       red();
       printf("\n\n\t\tEnter player two name : ");
       gets(TWO.name);//get player two's name
   }
   int len1 = strlen(ONE.name);//set lengths of two names
   int len2 = strlen(TWO.name);
    system("cls");
    int valid = 0, choice = 0, n;
    green();
    printf("\n\n\t\tChoose difficulty :-"
           "\n\n\t\tBeginner mode(enter : 1)"
           "\n\n\t\tAmateur mode(enter : 2)"
           "\n\n\t\tAdvanced mode(enter : 3)"
           "\n\n\n\n\t\tBack(enter : 4)"
           "\n\n\t\tBack to main menu(enter : 5)\n\n");


    while(valid != 1 || choice > 5 || choice < 1)//get the game difficulty
   {
        printf("\t\tEnter the number of your choice : ");
        valid = scanf("%d", &choice);
        while(valid != 1)
        {
            printf("\n\tThis is invalid choice\n");
            scanf("%*[^\n]");//copied from youtube
            printf("\tPlease enter 1 or 2 or 3 or 4 or 5 : ");
            valid = scanf("%d", &choice);

        }
   }
   reset();
   if(choice == 1)//beginner(easy) 2*2 grid
   {
       n = 2;//dim. of grid as boxes
       int TotalMoves = 2*n*(n + 1);//no of moves available
       int size = 2*n + 2;//real dim. of grid
       char grid[6][6], dot = 254;
       /*i and j are just counters
       MovesPlayed -> no. of moves of two players
       gamer -> no. of player who play*/
       int j, i, MovesPlayed = 0, gamer = 1;
       /*GameDetails is a 2d array contain details of each move :
       every row shows a move as :
       col. 1 -> the choosen row
       col. 2 -> the choosen col.
       col. 3 -> no. of player who played this move
       col. 4, 5, 6 and 7 -> indexes of boxes closed (if exist) (one box or two boxes(chain))
       col. 8 -> no. of times the computer win a box or two boxes*/
       int GameDetails[TotalMoves][8];
       for(i = 0; i < TotalMoves; i++)//make sure all elements are zeros to avoid random values
       {
           for(j = 0; j < 8; j++)
           {
               GameDetails[i][j] = 0;
           }
       }


    for(i = 0; i < size; i++){//make sure all elements of grid are empty
        for(j = 0; j < size; j++){
            grid[i][j] = 32;
        }
    }


    //set numbers row and col. and set dots in grid
    for(i = 1; i < size; i++)
        {
        grid[i][0] = i;
        grid[0][i]= i;
        }
    for(i = 1; i < size; i+=2){
        for(j=1; j < size; j+=2){
            grid[i][j] = dot;
        }
    }

    //start playing :)
    GameLoop(size, grid, len1, len2, ONE.name, TWO.name, ONE.score, TWO.score, ONE.NoOfMoves, TWO.NoOfMoves, mode, TotalMoves, GameDetails, MovesPlayed, gamer, top);
   }else if(choice == 2)//Amateur(expert) mode 5*5 grid
   {
       //the remaining is as previous
       n = 5;
       char grid[12][12];
       int TotalMoves = 2*n*(n + 1);
       int size = 2*n + 2;
       int j, i, MovesPlayed = 0, gamer = 1;
       char dot = 254;
       int GameDetails[TotalMoves][8];
       for(i = 0; i < TotalMoves; i++)
       {
           for(j = 0; j < 8; j++)
           {
               GameDetails[i][j] = 0;
           }
       }

    for(i=0; i < size; i++){
        for(j=0; j < size; j++){
            grid[i][j]=32;
        }
    }



    for(i=1; i < size; i++)
        {
        grid[i][0]=i;
        grid[0][i]=i;
        }
    for(i=1; i < size; i+=2){
        for(j=1; j < size; j+=2){
            grid[i][j] = dot;
        }
    }


    GameLoop(size, grid, len1, len2, ONE.name, TWO.name, ONE.score, TWO.score, ONE.NoOfMoves, TWO.NoOfMoves, mode, TotalMoves, GameDetails, MovesPlayed, gamer, top);
   }else if(choice == 3)//advanced mode(extra feature) 8*8 grid
   {
       //the remaining is as previous
       n = 8;
       char grid[18][18], dot = 254;
       int TotalMoves = 2*n*(n + 1);
       int size = 2*n + 2;
       int j, i, MovesPlayed = 0, gamer = 1;
       int GameDetails[TotalMoves][8];
       for(i = 0; i < TotalMoves; i++)
       {
           for(j = 0; j < 8; j++)
           {
               GameDetails[i][j] = 0;
           }
       }

    for(i=0; i < size; i++){
        for(j=0; j < size; j++){
            grid[i][j]=32;
        }
    }

    //here the grid is large (18*18) which meaning its dim. is larger than hexadecimal numbers, we use 'g' and 'h' to conserve the grid shape
    for(i=1; i < size; i++)
        {
        if(i == 16)
        {
            grid[i][0] = 'g';
            grid[0][i] = 'g';
        }else if(i == 17)
        {
            grid[i][0] = 'h';
            grid[0][i] = 'h';
        }else
        {
        grid[i][0] = i;
        grid[0][i] = i;
        }
    }
    for(i=1; i < size; i+=2){
        for(j=1; j < size; j+=2){
            grid[i][j] = dot;
        }
    }

    GameLoop(size, grid, len1, len2, ONE.name, TWO.name, ONE.score, TWO.score, ONE.NoOfMoves, TWO.NoOfMoves, mode, TotalMoves, GameDetails, MovesPlayed, gamer, top);
   }else if(choice == 4)
   {
       system("cls");
       StartNewGame(top);
       return;
   }else if(choice == 5)
   {
       system("cls");
       main();
       return;
   }



   return;
}


