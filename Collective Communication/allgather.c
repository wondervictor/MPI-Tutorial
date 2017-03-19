/*
 * Author: Vic Chan
 * Date: 2017-3-19
 * Title: Alltoghter
 */

#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {

    int rank, commSize;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int sum = 0;
    for(int i = 0; i < 4; i ++) {
        sum += rank * 4 + i;
    }
    int buf[commSize];
    fprintf(stdout, ">>> proc %d sum %d\n", rank, sum);

    MPI_Allgather(&sum, 1, MPI_INT, buf, 1, MPI_INT, MPI_COMM_WORLD);

    for(int i = 0; i < commSize; i ++) {
        fprintf(stdout, ">>> proc %d index %d sum %d\n", rank, i, buf[i]);
    }
    MPI_Finalize();

    return 0;
}
