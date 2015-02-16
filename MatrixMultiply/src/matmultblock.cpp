#include <stdlib.h>
#include <stdio.h>

#include "timer.h"


#define IND(A, x, y, d) A[(x)*(d)+(y)]

// C = A * B
void mult(int N, int L, int M, double *A, double*B, double *C)
{
    double *pA, *pB, *pC;
    TimePoint started, ended, timeTaken;

    started = Now();

    for(int i=0; i<N; ++i, pA+=L)
        for(int j=0; j<M; ++j, ++pC, pB=B+j) {
            double *tpA = pA;
            for(int k=0; k<L; ++tpA, ++k, pB+=M)
                *pC += *tpA * (*pB);
        }
    ended = Now();
    printf("mult Time: %d ms\n", ToMilli(ended-started));
}

void mult_trans(int N, int L, int M, double *A, double*B, double *C)
{
    double *Bx;
    double *pA, *pB, *pC, *pBx;
    TimePoint started, ended, timeTaken;


    pBx = Bx = (double*) calloc(L*M, sizeof(double));

    started = Now();

    for(int j=0; j < L; ++j, pBx = Bx+j)
        for(int k=0; k < M; ++k, ++pB, pBx+=M)
            *pBx = *pB;
    pBx = Bx;
    Bx = B;
    B = pBx;

    pA = A;
    pC = C;
    for(int i=0; i<N; ++i, pA+=L) {
        pB = B;
        for(int j=0; j<M; ++j, ++pC, pB+=L) {
            double *tpA = pA, *tpB = pB;
            for(int k=0; k<L; ++tpA, ++tpB, ++k)
                *pC += *tpA * (*tpB);
        }
    }
    ended = Now();
    printf("mult_trans Time: %d ms\n", ToMilli(ended-started));
    free(B);
}

static inline int min(int x, int y) {
    return y ^ ((x^y) & -(x<y));
}
void mult_blocked(int N, int L, int M, double *A, double*B, double *C)
{
    double *Bx;
    double *pA, *pB, *pC, *pBx;
    TimePoint started, ended, timeTaken;

    pBx = Bx = (double*) calloc(L*M, sizeof(double));

    started = Now();

    for(int j=0; j < L; ++j, pBx = Bx+j)
        for(int k=0; k < M; ++k, ++pB, pBx+=M)
            *pBx = *pB;
    pBx = Bx;
    Bx = B;
    B = pBx;

    pA = A;
    pC = C;
    pB = B;

//    const int x = N, y=M, z = L;
    const int blockM = 256;
    const int blockL = 256;
    for(int j=0; j<M; j+=blockM) {
        int jjEnd = min(j+blockM, M);
        for(int k=0; k<L; k+= blockL) {
            pC = C + j;
            int kkEnd = min(k+blockL, L);
            for(int i=0; i<N; ++i, pA+=L, pC+=M) {
                double *pC1 = pC;
                for(int jj=j; jj<jjEnd; ++jj, ++pC1){
                    pB = B + jj*L + k;
                    pA = A + i*L + k;
                    for(int kk=k; kk<kkEnd; ++kk, ++pB, ++pA)
                        *pC1 += *pB *(*pA);
                }// jj
            } // i
        } //k
    } // j


    ended = Now();
    printf("mult_blocked Time: %d ms\n", ToMilli(ended-started));
    free(B);
}

