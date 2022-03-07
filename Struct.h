#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

typedef struct//player structure to set a game
{
    char name[100];
    int score;
    int NoOfMoves;
}player;


typedef struct//structure containing informations for top10 list
{
      int len;
      char name[100];
      int score;
}TOP;

#endif // STRUCT_H_INCLUDED
