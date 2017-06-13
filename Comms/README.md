## Communicator 通信子


获取通信子内进程个数

````
MPI_Comm_Size(comm, *size);
````

通信子决定通信环境，MPI程序启动后，会自动创建两个通信环境：MPI_COMM_WORLD和MPI_COMM_SELF.

通信子：组内通信子和组间通信子

组：一组进程标示所组成的有序集合，组内每个进程都有一个rank标示。

注意 组 和 通信子之间的关系


#### 组管理

1. 返回相关组

````
int MPI_Comm_group(MPI_Comm, MPI_Group* )
````

2. 释放组对象

````
int MPI_Group_free(MPI_Group*)
````

3. 两个组并集

````
MPI_Group_union(MPI_Group group1,MPI_Group group2, MPI_Group* newGroup)
````
进程顺序从group1 到 group2

4. 两个组交集

````
MPI_Group_intersection(MPI_Group group1,MPI_Group group2, MPI_Group* newGroup)
````
进程顺序从group1 到 group2

5. 用已知组创建新组(include)

````
int MPI_Group_incl(MPI_Group group, int n, int *ranks, MPI_Group* newGroup)
````

利用已有进程组的中n个进程`ranks[0], ranks[1].....ranks[n-1]` 来创建新group

6. 用已知组创建新组(exclude)

````
int MPI_Group_excl(MPI_Group group, int n, int *ranks, MPI_Group* newGroup)
````

利用已有进程组的中n个进程`ranks[0], ranks[1].....ranks[n-1]` 来创建新group

7. 用已知组和范围创建新组(include, range)

````
int MPI_Group_range_incl(MPI_Group grp, int n, int ranges[][3], MPI_Group *newGroup)
````
利用三元组(first, last, stride)来分割已有进程组获得新组

如 ranges = {{1,9,2},{15,20,3}}

得到的进程为 {1,3,5,7,9,15,18}

8. 用已知组和范围创建新组(exclude, range)

````
int MPI_Group_range_excl(MPI_Group grp, int n, int ranges[][3], MPI_Group *newGroup)
````

利用三元组(first, last, stride)来分割已有进程组获得新组


#### 通信子管理

通信子创建

````
int MPI_Comm_create(MPI_Comm originComm, MPI_Group group, MPI_Comm* newComm)
````

利用已有通信子和相应的 Group 来创建新的通信子。

分割通信子

````
int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm* newComm)
````


##### 组间通信



