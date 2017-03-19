/*
 * Author: Vic Chan
 * Date: 2017-3-19
 * Title: reduce
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
    for (int i = 0; i < 10; i ++) {
        sum += rank * 10 + i;
    }

    if (rank == 0) {
        int allSum = 0;
        fprintf(stdout, ">>> proc %d reduce sum %d\n", rank, sum);
        MPI_Reduce(&sum, &allSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        fprintf(stdout, ">>> proc %d all sum %d\n", rank, allSum);

    } else {
        fprintf(stdout, ">>> proc %d reduce sum %d\n", rank, sum);
        MPI_Reduce(&sum, NULL, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
