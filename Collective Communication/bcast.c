/*
 * Author: Vic Chan
 * Date: 2017-3-19
 * Title: bcast
 */

#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {

    int rank, commSize;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int value = 0;
    if(rank == 0) {
        value = 10;
        MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);
        fprintf(stdout, ">>> proc %d bcast value: %d\n", rank, value);
    } else {
        MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);
        fprintf(stdout, ">>> proc %d get value: %d\n", rank, value);
    }
    MPI_Finalize();

    return 0;
}
