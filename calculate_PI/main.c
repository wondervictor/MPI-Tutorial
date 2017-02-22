#include <stdio.h>
#include "mpi.h"



double calculate_part(int start, int step);


int main(int argc, char *argv[]) {

    int my_rank, comm_size;
    int N = 1024 * 1024;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    int step = (int)(N/comm_size);
    int start = my_rank * step;
    double value = calculate_part(start, step);
    double result = 0.0;
    if (my_rank == 0) {
        result += value;
        for(int i = 1; i < comm_size; i ++) {
            MPI_Recv(&value, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            result += value;
        }
        printf("pi is : %0.15f\n",result * 4);
    } else {
        MPI_Send(&value, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}


double calculate_part(int start, int step) {
    double sum = 0.0;
    int flag = 1;
    for(int i = 0; i < step; i ++) {
        if(start%2!=0)
            flag = -1;
        else
            flag = 1;

        sum += flag * (1/(double)(2*start+1));
        start ++;
    }
    return sum;
}
