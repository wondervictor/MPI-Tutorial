/*
 * Author: Vic Chan
 * Date: 2017-3-19
 * Title: Allreduce
 */

#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {

    int rank, commSize;
    MPI_Init(&argc, &argv)
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int sumRank = 0.0;

    int rankCpy = rank;

    MPI_Allreduce(&rankCpy, &sumRank, 1, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);

    printf(">>>proc %d sum %d\n", rank, sumRank);

    MPI_Finalize();

    return 0;
}
