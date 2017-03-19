/*
 * Author: Vic Chan
 * Date: 2017-3-19
 * title: scatter
 */

#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {

    int rank, commSize;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    float recvBuf[3];

    if(rank == 0) {
        float sendBuf[3][4] = {
            {1.0, 2.0, 3.0, 4.0},
            {5.0, 6.0, 7.0, 8.0},
            {9.0, 10.0, 11.0, 12.0},
        };
        MPI_Scatter(sendBuf, 3, MPI_FLOAT, recvBuf, 3, MPI_FLOAT, 0, MPI_COMM_WORLD);
    } else {
        MPI_Scatter(NULL, 0, MPI_FLOAT, recvBuf, 3, MPI_FLOAT, 0, MPI_COMM_WORLD);
    }
    float sum = 0.0;
    for(int i = 0; i < 3; i ++) {
        sum += recvBuf[i];
    }
    fprintf(stdout, ">>> proc cal sum = %f\n", sum);
    MPI_Finalize();

    return 0;
}
