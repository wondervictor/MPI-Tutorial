#include "vector_matrix.h"
#include "mpi.h"




// Use Scatter
void sum_vectors(int rank, int comm_size, double *x, double *y ,double *z, int n) {
    int num_per_process = n / comm_size;
    double x_temp_data[num_per_process];
    double y_temp_data[num_per_process];

    MPI_Scatter(x, num_per_process, MPI_DOUBLE, x_temp_data, num_per_process, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(y, num_per_process, MPI_DOUBLE, y_temp_data, num_per_process, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    int __start = rank * num_per_process;
    for(int i = 0; i < num_per_process; i ++) {
        int id = __start + i;
        z[id] = x_temp_data[i] + y_temp_data[i];
    }

}

// Use Scatter and Gather --- Failed
void sum_vectors_scatter_gatter(int rank, int comm_size, double *x, double *y ,double *z, int n) {
    int num_per_process = n / comm_size;
    double x_temp_data[num_per_process];
    double y_temp_data[num_per_process];

    MPI_Scatter(x, num_per_process, MPI_DOUBLE, x_temp_data, num_per_process, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(y, num_per_process, MPI_DOUBLE, y_temp_data, num_per_process, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    int __start = rank * num_per_process;
    for(int i = 0; i < num_per_process; i ++) {
        int id = __start + i;
        x_temp_data[id] = x_temp_data[i] + y_temp_data[i];
    }
    MPI_Gather(x_temp_data,num_per_process,MPI_DOUBLE, y_temp_data, num_per_process, MPI_DOUBLE, 0, MPI_COMM_WORLD);
}
