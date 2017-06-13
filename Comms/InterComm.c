
#include <stdio.h>
#include <mpi.h>


// P2P


void interP2P(int bufSize, int rank, int membershipKey, MPI_Comm* comm);

int main(int argc, char* argv[]) {

    MPI_Comm myComm;
    // 组间
    MPI_Comm firstComm;
    // 组间
    MPI_Comm secondComm;

    int membershipKey, rank;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    membershipKey = rank % 3;

    MPI_Comm_split(MPI_COMM_WORLD, membershipKey, rank, &myComm);

    if(membershipKey == 0) {
        // first
        MPI_Intercomm_create(myComm, 0, MPI_COMM_WORLD, 1,1,&firstComm);
        fprintf(stdout,"proc %d first call end\n", rank);

    } else if (membershipKey == 1) {
        // second
        MPI_Intercomm_create(myComm, 0, MPI_COMM_WORLD, 0, 1,&firstComm);
        fprintf(stdout,"proc %d second call 0 end\n", rank);

        MPI_Intercomm_create(myComm, 0, MPI_COMM_WORLD, 2, 2,&secondComm);
        fprintf(stdout,"proc %d second call 2 end\n", rank);

    } else if (membershipKey == 2) {
        // third
        MPI_Intercomm_create(myComm, 0, MPI_COMM_WORLD, 1,2,&firstComm);
        fprintf(stdout,"proc %d third call end\n", rank);
    }
    interP2P(10,rank, membershipKey, &myComm);
    switch (membershipKey) {
        case 1:
            MPI_Comm_free(&firstComm);
            MPI_Comm_free(&secondComm);
            break;
        case 0:
            MPI_Comm_free(&firstComm);
            break;
        case 2:
            MPI_Comm_free(&firstComm);
            break;

    }

    MPI_Finalize();
}


void interP2P(int bufSize, int rank, int membershipKey, MPI_Comm* comm) {
    int i, myRank, mySize;
    int sendBuf[bufSize];
    int recvBuf[bufSize];
    char outputStr[500];
    MPI_Request sreq1, rreq1;
    MPI_Status sstatus1, rstatus1;

    if (membershipKey == 0) {
        MPI_Comm_rank(*comm, &myRank);
        MPI_Comm_size(*comm, &mySize);
        for(int i = 0; i < bufSize; i ++) {
            sendBuf[i] = myRank * mySize + i;
        }
        if (rank == 0) {
            MPI_Issend(sendBuf, bufSize, MPI_INT, 1, 123, *comm, &sreq1);
            MPI_Wait(&sreq1, &sstatus1);
        }
    } else if (membershipKey == 1) {
        MPI_Comm_rank(*comm, &myRank);
        MPI_Comm_size(*comm, &mySize);
        if (rank == 1) {
            MPI_Irecv(recvBuf, bufSize, MPI_INT, 0, 123, *comm, &rreq1);

        }
        if (rank == 1) {
            MPI_Wait(&rreq1, &rstatus1);
            sprintf(outputStr, "Proc %d L: %d received n",rank, myRank);
            for (int i = 0; i < bufSize; i ++) {
                sprintf(outputStr, "%s rb[%d] = %d\n", outputStr,recvBuf[i], i);
            }
            fprintf(stdout, "%s\n", outputStr);
        }
    }

}