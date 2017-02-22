
#include "sum.h"
#include "mpi.h"

#define MAX(A,B) ((A)>(B)?(A):(B))

/* Use MPI Reduce */
int sum_reduce(int *arrays, int num, int rank, int comm_size) {
    int num_per_process = num/comm_size;
    int local_sum = 0;
    int __start = rank*num_per_process;
    for(int i = 0; i < num_per_process; i ++) {
        local_sum += arrays[__start + i];
    }
    int global_sum = 0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM,0,MPI_COMM_WORLD);
    if (rank == 0)
        return global_sum;
    else
        return local_sum;
}

/* Use MPI All Reduce */
int sum_all_reduce(int *arrays, int num, int rank, int comm_size) {
    int num_per_process = num/comm_size;
    int local_sum = 0;
    int __start = num_per_process * rank;
    for(int i = 0; i < num_per_process; i ++)
        local_sum += arrays[__start + i];
    int global_sum = 0;
    MPI_Allreduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    return global_sum;
}


/* */
int max_reduce(int *arrays, int num, int rank, int comm_size) {
    int num_per_process = num / comm_size;
    int __start = num_per_process * rank;
    int max = arrays[__start];
    for(int i = 1; i < num_per_process; i ++) {
        MAX(max, arrays[__start + i]);
    }
    int global_max = 0;
    MPI_Reduce(&max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    if(rank == 0)
        return global_max;
    else
        return 0;
}


double mean_reduce(int *arrays, int nums, int rank, int comm_size) {
    

    return 0.0;
}
