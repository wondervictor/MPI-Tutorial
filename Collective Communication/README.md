# 集合通信

## MPI_Bcast

**1->N**

* 函数原型

````
MPI_Bcast(*buf, count, MPI_TYPE, srcProc, comm);
// 一般为 MPI_COMM_WORLD 对于当前通信子的全部进程
````

* 作用

数据分发，广播，每个进程有相同的数据。


## MPI_Scatter

**1->N**

* 函数原型

````
MPI_Scatter(sendBuf, sendCount, MPI_TYPE, recvBuf, receiveCount, MPI_TYPE, srcProc, MPI_COMM_WORLD);
````

* 作用

数据分发，从根进程向每个进程分发不同的数据。


* 样例

````
float recvBuf[4];
if(rank == 0) {
    float sendBuf[4][4] = {
        {1.0, 2.0, 3.0, 4.0},
        {5.0, 6.0, 7.0, 8.0},
        {9.0, 10.0, 11.0, 12.0},
        {13.0, 14.0, 15.0, 16.0}
    };
    // 根进程发送数据
    MPI_Scatter(sendBuf, 4, MPI_FLOAT, recvBuf, 4, MPI_FLOAT, 0, MPI_COMM_WORLD);
} else {
    // 其他进程接受数据
    MPI_Scatter(NULL, 0, MPI_FLOAT, recvBuf, 4, MPI_FLOAT, 0, MPI_COMM_WORLD);
}
````



## MPI_Scatterv


**1->N**

* 函数原型

```
int MPI_Scatterv(const void *sendbuf,
                 const int sendcounts[],
                 const int displs[],
                 MPI_Datatype sendtype,
                 void *recvbuf,
                 int recvcount,
                 MPI_Datatype recvtype,
                 int root,
                 MPI_Comm comm)
```
* sendCount[] 用于存放每个进程发送的元素个数
* displs[] 用于存放每个进程获取元素的起始位置

* 作用

向不同进程发送不同长度的消息


## MPI_Gatter


**N->1**

* 函数原型


```
MPI_Gather(&sendbuf, sendCount, MPI_INT, recvBuf, recvCount, MPI_INT, srcProc, MPI_COMM_WORLD);
```

* 作用

数据聚合，将数据聚集到某一个进程

* 样例

```
// 发送一个数字到主进程
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
```

## MPI_Gatherv

* 函数原型


````
int MPI_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                void *recvbuf, const int *recvcounts, const int *displs,
                MPI_Datatype recvtype, int root, MPI_Comm comm)
````

* 作用

从每个进程中获取不同数量的数据



## MPI_Reduce


* 函数原型

```
MPI_Reduce(sendBuf,recvBuf, count, MPI_TYPE, MPI_OPERATOR, Target_RANK, MPI_COMM_WORLD);
```

* 作用

向一个进程归约

可选操作

`MPI_SUM`, `MPI_MAX`, `MPI_MIN`,`MPI_....`

* 样例

````
// 向0号进程发送一个数，取和
if (rank == 0) {
    int allSum = 0;
    fprintf(stdout, ">>> proc %d reduce sum %d\n", rank, sum);
    MPI_Reduce(&sum, &allSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    fprintf(stdout, ">>> proc %d all sum %d\n", rank, allSum);

} else {
    fprintf(stdout, ">>> proc %d reduce sum %d\n", rank, sum);
    MPI_Reduce(&sum, NULL, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
}
````
