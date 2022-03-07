//function to read hexadecimal numbers and 'g'&'h' in case of 8*8 boxes grid
#include <string.h>
#include <stdio.h>


int HexaScan()
{
    char scan[100];
    int decimal;
    fflush(stdin);
    gets(scan);//we get string to avoid crashing
    if(scan[0] > 48 && scan[0] < 58)//from 0 to 9
    {
        decimal = scan[0]-48;
    }else if(scan[0] > 96 && scan[0] < 105){//from a to h
        decimal = scan[0]-87;
    }else{
        decimal = -1;//invalid input
    }
    return decimal;
}
