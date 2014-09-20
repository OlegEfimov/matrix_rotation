// old_rotation.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#define r 5
#define randomize() srand((unsigned)time(NULL));
#define random(p) ((int)(rand()*p/RAND_MAX))
int Matr1[r][r];
int Matr2[r][r];

int _tmain(int argc, _TCHAR* argv[])
    {
    short i, j;

    for (i=0; i<r; i++)
        for (j=0; j<r; Matr1[i][j++]=i*r + j);

    printf("Matrix initial:\n");
    for (i=0; i<r; i++, printf("\n"))
        for (j=0; j<r; printf("%3d  ", Matr1[i][j++]));

    for (i=0; i<r; i++)
        for (j=0; j<r; j++)
            Matr2[j][r-1-i]=Matr1[i][j];

    printf("\nMatrix rotated 90deg:\n");
    for (i=0; i<r; i++, printf("\n"))
        for (j=0; j<r; printf("%3d  ", Matr2[i][j++]));

    system("pause"); 

    return 0;
    }


