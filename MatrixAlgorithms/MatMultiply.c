/**
 * Author: VicChan
 * Content: Matrix Multiplication by MPI
 * */


#include <mpi.h>
#include <stdio.h>
#include "GenMat.h"
#include <stdlib.h>
#include <time.h>

int multiply(int* a, int *b, int dim) {
    int res;
    for(int i = 0; i < dim; i ++) {
        res += a[i] * b[i];
    }
    return res;
}

int main(int argc, char* argv[]){

    srand((unsigned)time(0));


    int myRank, commSize;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    int a[64];
    int b[64];

    int cal_a[8];
    int cal_b[8];

    mat(8, 8, b);

    if (myRank == 0) {
        mat(8, 8, a);
        printMat(8, 8, b);
        printMat(8, 8, a);
        MPI_Scatter(a,8,MPI_INT, &cal_a, 8, MPI_INT, 0, MPI_COMM_WORLD);

    } else {
        MPI_Scatter(a,8,MPI_INT, &cal_a, 8, MPI_INT, 0, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    fprintf(stdout, "Start to compute in proc %d\n", myRank);
    int res[8];
    int local_res;
    for(int i = 0; i < 8; i ++) {
        for (int j = 0; j < 8; j ++){
            local_res += b[j * 8 + i] * cal_a[i];
        }
        res[i] = local_res;
        local_res = 0;
        printf("proc %d value:%3d\n", myRank, res[i]);
    }

    int result[64];
    MPI_Gather(res, 8, MPI_INT, result,8, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    if (myRank == 0 ) {
        printMat(8,8,result);
    }
}


