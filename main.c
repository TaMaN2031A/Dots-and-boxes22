#include <stdio.h>
#include <stdlib.h>
#include "color.h"
#include "PrintArrays.h"
#include "play.h"
#include "Struct.h"



void SortArray(TOP a[10]);


int main()
{
     TOP top[10] = {0};//top10 list(array of structures TOP)
        FILE *leader = fopen("T.txt", "r");
        if(leader == NULL)
        {
            //if the game runs for 1st time or the file was deleted
            leader = fopen("T.txt", "w");
            fclose(leader);
            leader = fopen("T.txt", "r");
        }

        //reading the file
        int i;
        for(i = 0; i < 10; i++)
        {
            fread(&top[i].len, sizeof(int), 1, leader);
            fread(top[i].name, sizeof(char), top[i].len, leader);
            top[i].name[top[i].len] = '\0';
            fread(&top[i].score, sizeof(int), 1, leader);
        }
        fclose(leader);
        SortArray(top);//sort the list
    cyan();
    printf("\t\t\t\t\t\tWelcome to our project\n");
    printf("\t\t\t\t\t\t  Dots & Boxes game\n\n");
    green();
    printf("\n\n\tPlay(enter : 1)"
           "\n\n\tTop 10 list(enter : 2)"
           "\n\n\tExit(enter : 3)\n\n\n");
   int choice = 0;

   int valid = 0;

   //take choice and check validity
   while(valid != 1 || choice < 1 || choice > 3)
   {
        printf("\tEnter the number of your choice : ");
        valid = scanf("%d", &choice);
        while(valid != 1)
        {
            printf("\n\tThis is invalid choice\n");
            scanf("%*[^\n]");//copied from youtube
            printf("\tPlease enter 1 or 2 or 3 : ");
            valid = scanf("%d", &choice);

        }
   }
   system("cls");
   switch(choice)
   {
   case 1 :
    play(top);
    break;
   case 2 :
       //print the top10 list
       for(int i = 1; i <= 10; i++)
       {
           printf("%d- ", i);
           for(int j = 0; j < top[i-1].len; j++)
           {
               printf("%c", top[i-1].name[j]);
           }
           printf(" %d\n", top[i-1].score);
       }
       cyan();
       printf("\n\n\n\t\tPress enter to back");
       reset();
       char f[5];
       fflush(stdin);
       gets(f);
       system("cls");
       main();
       break;
   case 3 :
    //close the game
    return 0;
   }



}

void SortArray(TOP a[])//function to sort the top10 list
{
    int i, j;
    TOP temp;
    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            if(a[j].score < a[j+1].score)
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}
