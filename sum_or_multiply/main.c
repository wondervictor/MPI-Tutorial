#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"
#include "sum.h"


int main(int argc, char *argv[]) {
    int my_rank, comm_size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int a[32];
    for(int i = 0; i < 32; i ++) {
        a[i] = i + 1;
    }

    /* ****All Reduce**** */
    int result = sum_all_reduce(a, 32, my_rank, comm_size);
    printf("result is %d from proc %d\n",result, my_rank);

    /* ****Reduce*****

    int result = sum_reduce(a,32,my_rank,comm_size);
    if(my_rank == 0) {
        printf("MAIN OUTPUT is %d\n", result);
    } else {
        printf("PROC %d result is %d\n",my_rank, result);
    }
    */


    /* *****BroadCast******

    int value = 0;
    if(my_rank == 0) {
        value = 10;
        printf("rank %d value broadcast\n",my_rank);
        MPI_Bcast(&value,1,MPI_INT, 0, MPI_COMM_WORLD);
    } else {
        MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);
        printf("rank %d get the value is %d\n",my_rank,value);
    }
    */
    MPI_Finalize();


    return 0;
}
