#ifndef GAMELOOP_H_INCLUDED
#define GAMELOOP_H_INCLUDED

int BoxCheck(int size, char *grid[][size], int gamer);
void GameLoop(int size, char grid[][size],int len1, int len2, char name1[], char name2[], int *score1, int *score2, int *Moves1, int *Moves2, int mode, int TotalMoves, int GameDetails[][3], int *MovesPlayed, int gamer);

#endif // GAMELOOP_H_INCLUDED
