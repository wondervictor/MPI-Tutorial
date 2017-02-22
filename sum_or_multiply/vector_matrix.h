#ifndef _VECTOR_MATRIX_H_
#define  _VECTOR_MATRIX_H_


void sum_vectors(int rank, int comm_size, double *x, double *y ,double *z, int n);

void sum_vectors_scatter_gatter(int rank, int comm_size, double *x, double *y ,double *z, int n);

#endif //_VECTOR_MATRIX_H_
