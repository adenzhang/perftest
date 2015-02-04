#include <stdlib.h>
#include <stdio.h>
#include <cblas.h>

#include "timer.h"

inline void swap(int& x, int &y) {
    x = x^y;
    y = x^y;
    x = x^y;
}
inline int min(int x, int y) {
    return y ^ ((x^y) & -(x<y));
}
inline int least_significant_bit(int x) {
    return x & (-x);
}

void mult_blas(int N)
{
    double *A, *B, *C;
    TimePoint started, ended, timeTaken;

    A = (double*) calloc(N*N, sizeof(double));
    B = (double*) calloc(N*N, sizeof(double));
    C = (double*) calloc(N*N, sizeof(double));

    int i,j;
    started = Now();

    cblas_dgemm(CblasColMajor, CblasTrans, CblasTrans, N, N, N, 1,B, N, C, N, 0, A, N);

    ended = Now();
    printf("blas Time: %d ms\n", ToMilli(ended-started));
    free(A);
    free(B);
    free(C);
}

int main(int argc, char *argv[])
{
    void mult(int N);
    void mult_trans(int N);

    const int N = 1024;
    mult_blas(N);
    mult(N);
    mult_trans(N);
}
