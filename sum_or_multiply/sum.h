#ifndef _SUM_H_
#define _SUM_H_

int sum_reduce(int *arrays, int num, int rank, int comm_size);

int sum_all_reduce(int *arrays, int num, int rank, int comm_size);

int max_reduce(int *arrays, int num, int rank, int comm_size);

double mean_reduce(int *arrays, int nums, int rank, int comm_size);

#endif // _SUM_H_
