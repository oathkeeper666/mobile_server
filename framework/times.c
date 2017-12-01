#include "times.h"

static ulong_t current_msec;
static char fmt_time[TIME_LEN];

void time_init()
{
	time_update();
}

void time_update()
{
	struct timeval tv;
	time_t sec;
	uint_t msec;
	struct tm tm;

	gettimeofday(&tv, NULL);

	sec = tv.tv_sec;
	msec = tv.tv_usec / 1000;
	current_msec = (ulong_t) sec * 1000 + msec;

	localtime_r(&sec, &tm);
	sprintf(fmt_time, "%4d/%02d/%02d %02d:%02d:%02d:%03d",
    	tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, msec);
}
