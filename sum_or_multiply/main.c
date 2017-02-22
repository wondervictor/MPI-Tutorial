#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"
#include "sum.h"
#include "vector_matrix.h"
#include <time.h>

int main(int argc, char *argv[]) {
    int my_rank, comm_size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);






    /* ****With Gatter But Failed****

    double x[32];
    double y[32];
    double z[32] = {0};
    for(int i = 0; i < 32; i ++) {
        x[i] = (double)i/2;
    }
    for(int i = 0; i < 32; i ++) {
        y[i] = (double)(2 * i - 1);
    }
    // sum_vectors(my_rank, comm_size, x, y, z, 32);

    sum_vectors_scatter_gatter(my_rank, comm_size, x, y, z, 32);
    if(my_rank == 0) {
        printf("sum vector is: ");
        for(int i = 0; i < 32; i ++) {
            printf("%f ", z[i]);
        }
        printf("\n");
    }
    */
    srand(time(NULL));
    /* ****Scatter without Gatter**** */
    int a[32];
    for(int i = 0; i < 32; i ++) {
        a[i] = rand()%100;

    }
    int max_global = max_reduce(a, 32, my_rank, comm_size);
    // sum_vectors(my_rank, comm_size, x, y, z, 32);
    if(my_rank == 0) {

        for(int i = 0; i < 32; i ++) {
            printf(" %d ", a[i]);
        }

        printf("\nmax is %d\n", max_global);
    }


    /* ****All Reduce****
    int a[32];
    for(int i = 0; i < 32; i ++) {
        a[i] = i + 1;
    }

    int result = sum_all_reduce(a, 32, my_rank, comm_size);
    printf("result is %d from proc %d\n",result, my_rank);
    */

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
