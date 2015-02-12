#include <math.h>

#define MAXA 10000
const int maxa_half = MAXA/2;

struct AARR {
    int A[MAXA];

    int incA[MAXA];

    int rndA[MAXA];
};
static AARR gA;
static void init() {
    for(int i=0; i<MAXA; ++i) {
        gA.incA[i] = i;
//        gA.rndA[i] = rand();
    }
}

void test_LoopOpt() {
    //
}
