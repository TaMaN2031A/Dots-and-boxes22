#include <stdio.h>
#include <stdlib.h>
#include "color.h"

void Print2DcharArray(int n, int m, char a[][m])
{
    int i, j;
    for(i=0; i < n; i++){
        for(j=0; j < m; j++){
            printf("%c ", a[i][j]);
        }
        printf("\n");
    }
    return;
}

void Print1DintArray(int a[], int n)
{
    int i;
    for(i=0; i < n; i++){
        printf("%d ", a[i]);
    }
    return;
}

void Print1DarrayVertically(int a[], int n)
{
    int i;
    for(i=0; i < n; i++){
        printf("%d\n", a[i]);
    }
    return;
}
