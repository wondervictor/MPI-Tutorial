#include <mpi.h>
#include <stdio.h>


int main(int argc, char* argv[]) {

    int rank,rankSize;
    int color, key;

    MPI_Comm interComm, myComm;

    MPI_Group left, right, MPI_GROUP_WORLD, sub;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &rankSize);

    if (rankSize != 8) {
        fprintf(stdout, "This demo was limited to 8 procs\n");
        MPI_Finalize();
        return 0;
    }

    color = rank%2;

    int rankSp;

    MPI_Comm_group(MPI_COMM_WORLD, &MPI_GROUP_WORLD);

    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &myComm);

    if (color == 0) {
        MPI_Intercomm_create(myComm,0,MPI_COMM_WORLD,1,1,&interComm);
        MPI_Comm_group(interComm, &left);
        int leftExcl[2] = {0,2};
        MPI_Group_excl(left, 2,leftExcl, &sub);
        MPI_Comm_rank(interComm, &rankSp);
    } else {
        MPI_Intercomm_create(myComm,0,MPI_COMM_WORLD,0,1,&interComm);
        MPI_Comm_group(interComm, &right);
        int rightExcl[2] = {1,3};
        MPI_Group_excl(right, 2,rightExcl, &sub);
        MPI_Comm_rank(interComm, &rankSp);
    }

    fprintf(stdout, "rank %d color %d\n", rankSp, color);

    MPI_Comm_free(&interComm);
    MPI_Group_free(&sub);
    MPI_Finalize();







}