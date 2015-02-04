#include <stdlib.h>
#include <stdio.h>

#include "timer.h"


#define IND(A, x, y, d) A[(x)*(d)+(y)]

// C = A * B
void mult(int N)
{
    const int M = N;  // N x M matrix
    double *A, *B, *C;
    double *pA, *pB, *pC;
    TimePoint started, ended, timeTaken;

    pA = A = (double*) calloc(N*M, sizeof(double));
    pB = B = (double*) calloc(N*M, sizeof(double));
    pC = C = (double*) calloc(N*M, sizeof(double));

    started = Now();

//    for(int j=0; j < N; ++j)
//        for(int k=0; k < N; ++k)
//            IND(Cx, j,k,N) = IND(C, k,j, N);

//    for(int i=0; i<N; ++i)
//        for(int j=0; i<N; ++j)
//            for(int k=0; k<N; ++k)
//                IND(C, i,j, N) += IND(A, i,k, N)*IND(B, k, j, N);


    for(int i=0; i<N; ++i, pA+=M)
        for(int j=0; j<M; ++j, ++pC, pB=B+j) {
            double *tpA = pA;
            for(int k=0; k<M; ++tpA, ++k, pB+=M)
                *pC += *tpA * (*pB);
        }
    ended = Now();
    printf("mult Time: %d ms\n", ToMilli(ended-started));
    free(A);
    free(B);
    free(C);
}

void mult_trans(int N)
{
    const int M = N;  // N x M matrix
    double *A, *B, *C, *Bx;
    double *pA, *pB, *pC, *pBx;
    TimePoint started, ended, timeTaken;

    pA = A = (double*) calloc(N*M, sizeof(double));
    pB = B = (double*) calloc(N*M, sizeof(double));
    C = (double*) calloc(N*N, sizeof(double));
    pBx = Bx = (double*) calloc(N*M, sizeof(double));

    started = Now();

    for(int j=0; j < N; ++j, pBx = Bx+j)
        for(int k=0; k < M; ++k, ++pB, pBx+=M)
            *pBx = *pB;

    pA = A;
    pC = C;
    for(int i=0; i<N; ++i, pA+=M) {
        pB = Bx;
        for(int j=0; j<M; ++j, ++pC) {
            double *tpA = pA;
            for(int k=0; k<M; ++tpA, ++k)
                *pC += *tpA * (*pB);
        }
    }
    ended = Now();
    printf("mult_trans Time: %d ms\n", ToMilli(ended-started));
    free(A);
    free(B);
    free(C);
    free(Bx);
}

void mult_multilines(int N)
{
    const int M = N;  // N x M matrix
    const int NLINES = 256;  // block size
    const int NSTRIP = N/NLINES;

    double *A, *B, *C, *Bx;
    double *pA, *pB, *pC, *pBx;
    TimePoint started, ended, timeTaken;

    pA = A = (double*) calloc(N*M, sizeof(double));
    pB = B = (double*) calloc(N*M, sizeof(double));
    C = (double*) calloc(N*M, sizeof(double));
    pBx = Bx = (double*) calloc(N*M, sizeof(double));

    started = Now();

    for(int j=0; j < N; ++j, pBx = Bx+j)
        for(int k=0; k < M; ++k, ++pB, pBx+=M)
            *pBx = *pB;

    pA = A;
    pC = C;
    for(int s=0; s < NSTRIP; ++s, pA += NLINES) {
        double *tpA = pA;
        double *tpB = pB;
        for(int i=0; i<N; ++i, tpA+=M) {
            pB = Bx;
            for(int j=0; j<M; ++j, ++pC) {
                double *tpA = pA;
                for(int k=0; k<M; ++tpA, ++k)
                    *pC += *tpA * (*pB);
            }
        }
    }
    ended = Now();
    printf("mult_trans Time: %d ms\n", ToMilli(ended-started));
    free(A);
    free(B);
    free(C);
    free(Bx);
}

