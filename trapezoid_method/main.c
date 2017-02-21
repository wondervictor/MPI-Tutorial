#include <stdio.h>
#include "mpi.h"


float calculate(float a, float b, int n, float h);

float f(float x);

int main(int argc, char *argv[]) {

    int my_rank, comm_size, n = 1024*1024, local_n;
    float a = 0.0, b = 3.0;
    float total, local_value;


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    float h = (b-a)/n;
    local_n = n / comm_size;

    float local_a = a + my_rank * h * local_n;
    float local_b = local_a + h * local_n;



    local_value = calculate(local_a,local_b, local_n, h);

    if (my_rank != 0) {
        printf("Process %d calculate %f\n", my_rank,local_value);
        MPI_Send(&local_value, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);

    } else {
        total = local_value;
        for(int i = 1; i < comm_size; i ++) {
            MPI_Recv(&local_value, 1, MPI_FLOAT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total += local_value;
        }
    }

    if(my_rank == 0) {
        printf("result is %f  from main process\n",total);
    }
    MPI_Finalize();

    return 0;
}

float f(float x) {
    return 3*x*x*x + 4*x*x + 12*x + 10;
}

float calculate(float a, float b, int n, float h) {
    float estimate, x;
    int i;
    estimate = (f(a)+f(b))/2.0;
    for(i = 1; i < n; i ++) {
        x = a + i * h;
        estimate += f(x);
    }
    estimate = estimate * h;
    return estimate;
}
