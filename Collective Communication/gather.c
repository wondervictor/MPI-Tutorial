/*
 * Author: Vic Chan
 * Date: 2017-3-19
 * Title: gather
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

    if(rank == 0) {
        int nums[commSize];
        fprintf(stdout, ">>>proc %d sum %d\n", rank, sum);
        MPI_Gather(&sum, 1, MPI_INT, nums, 1, MPI_INT, 0, MPI_COMM_WORLD);
        for(int i = 0; i < commSize; i ++) {
            printf(" %2d", nums[i]);
        }
        printf("\n>>>proc 0\n");
    } else {
        fprintf(stdout, ">>>proc %d sum %d\n", rank, sum);
        MPI_Gather(&sum, 1, MPI_INT, NULL, 0, MPI_INT, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
