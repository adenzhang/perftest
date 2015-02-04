#include "timer.h"

////=================== timer implementation ==========================
#ifdef USE_CHRONO
TimePoint Now()
{
return boost::chrono::steady_clock::now();
}
#else
long double Now()
{
long double atime=0;
#ifdef WIN32
static long long freq = 0;
long long a;
if( 0 == freq )
QueryPerformanceFrequency((LARGE_INTEGER*) &freq);
QueryPerformanceCounter((LARGE_INTEGER*)&a);
atime = (long double)a/(long double)freq * (long double)1.0E6;
#else
timespec t;
if( 0 == clock_gettime(0/*CLOCK_MONOTONIC*/, &t) )
atime = (long double)t.tv_sec * (long double)1.0E6 + (long double)t.tv_nsec / (long double)1.0E3;
#endif
return atime;
}
#endif

////=================== timer end ==========================
