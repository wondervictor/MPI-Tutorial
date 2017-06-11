//
// Created by VicChan on 2017/6/11.
//

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>




int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);

    int myRank, rankSize;
    int compareResult;

    int sendBuf[5] = {1,5,2,8,10};
    int recvBuf[5];

    int sendBuf2[6] = {4,5,1,3,7,8};
    int recvBuf2[6];

    int bufCount1 = 5;
    int bufCount2 = 6;

    MPI_Group MPI_GROUP_WORLD, newGroup;
    MPI_Comm commSlave, newComm;

    static int ranks[] = {0};

    MPI_Comm_group(MPI_COMM_WORLD, &MPI_GROUP_WORLD);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &rankSize);

    // create a group without 0
    MPI_Group_excl(MPI_GROUP_WORLD, 1, ranks, &newGroup);
    MPI_Comm_create(MPI_COMM_WORLD, newGroup, &commSlave);

    if(myRank != 0 ) {
        MPI_Comm_dup(commSlave, &newComm);
        MPI_Comm_compare(commSlave, newComm, &compareResult);
        fprintf(stdout, "MyRank is %d result=%d \n", myRank, compareResult);

    }

    MPI_Comm splitComm;
    MPI_Comm_split(MPI_COMM_WORLD, myRank%2, myRank, &splitComm);

    if (myRank != 0) {
        MPI_Reduce(sendBuf, recvBuf, bufCount1, MPI_INT, MPI_SUM, 1, commSlave);
        fprintf(stdout, "comm Slave %d reduced!\n", myRank);
    }

    MPI_Reduce(sendBuf2, recvBuf2, bufCount2, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    fprintf(stdout, "%d reduced!\n", myRank);
    if (myRank != 0 ) {
        MPI_Comm_free(&newComm);
        MPI_Comm_free(&commSlave);
    }
    MPI_Group_free(&MPI_GROUP_WORLD);
    MPI_Group_free(&newGroup);

    MPI_Finalize();



    return 0;
}
