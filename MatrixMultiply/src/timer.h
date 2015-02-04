#ifndef _AZ_TIMER_H
#define _AZ_TIMER_H

#include <time.h>


////=================== timer begin ==========================
// #define USE_CHRONO
#ifdef USE_CHRONO
#include <boost/chrono.hpp>
typedef boost::chrono::steady_clock::time_point TimePoint;
#define ToMicro(tp) boost::chrono::duration_cast<boost::chrono::microseconds>(tp).count()
#define ToMilli(tp) boost::chrono::duration_cast<boost::chrono::milliseconds>(tp).count()
TimePoint Now() ;
#else
typedef long double TimePoint;
#define ToMicro(x) int( x )
#define ToMilli(x) int( (x)/1000.0 )
long double Now();
#endif
#ifndef WIN32 // linux
#include <unistd.h>
#define Sleep(milli) usleep(milli*1000)
#endif

#endif
