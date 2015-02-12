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

// err = sum(sqr(Ai-Bi))
double matrix_err(int N, int M, double *A, double *B)
{
    double *pA = A, *pB=B;
    const int L = M*N;
    double r = 0;
    for(int i=0; i<L; ++i, ++pA, ++pB) {
        double x = *pA - (*pB);
        r += x*x;
    }
    return r;
}

void mult_blas(int N, int L, int M, double *A, double*B, double *C)
{
    TimePoint started, ended, timeTaken;

    int i,j;
    started = Now();

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1,A, N, B, N, 0, C, N);

    ended = Now();
    printf("blas Time: %d ms\n", ToMilli(ended-started));
}

int main(int argc, char *argv[])
{
    void mult(int N, int L, int M, double *A, double*B, double *C);
    void mult_trans(int N, int L, int M, double *A, double*B, double *C);

    double *A, *B, *C;
    const int N = 1024, L=1024, M=1024;

    A = (double*) calloc(N*N, sizeof(double));
    B = (double*) calloc(N*N, sizeof(double));
    C = (double*) calloc(N*N, sizeof(double));

    mult_blas(N, L, M, A, B, C);
    mult(N, L, M, A, B, C);
    mult_trans(N, L, M, A, B, C);

    free(A);
    free(B);
    free(C);
}
