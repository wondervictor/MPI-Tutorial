//
// Created by Vic Chan on 2017/6/13.
//

#include "GenMat.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>



void mat(int row, int col, int* matrix) {

    for(int i = 0; i < row; i ++) {
        for (int j = 0; j < col; j ++) {
            matrix[i*col + j] = rand() % 10;
        }
    }
}

void printMat(int row, int col, int* mat) {
    for (int i = 0; i < row; i ++) {
        for(int j = 0; j < col; j ++){
            printf("%d ", mat[col * i + j]);
        }
    }
    printf("\n");
}