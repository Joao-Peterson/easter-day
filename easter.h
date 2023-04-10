/**
 * Sources:
 * 
 * https://www.calendarbede.com/book/carter-easter-algorithm
 */

#ifndef _EASTER_HEADER_
#define _EASTER_HEADER_

#include <time.h>
#include <math.h>
#include <errno.h>

/**
 * @brief get easter day as struct tm. Based on calendarbede deduction
 * @param year: the year of reference
 */
struct tm easterDate(int year){
	
	double tmp;

	int a = year % 19;
	float k = year / 100;
	modf(k * 3/4 - 12, &tmp);
	int s = (int)tmp;
	modf(8 * (k - 14) / 25, &tmp);
	int m = (int)tmp;

	int ecclesiasticalFullMoon = 19 * a + 22 + s - m;
	int fullMoonMarchDay = ecclesiasticalFullMoon % 30 + 21;

	if(
		(fullMoonMarchDay == 49 && a > 10) ||
		(fullMoonMarchDay == 50)
	){
		fullMoonMarchDay--;
	}

	modf((float)year * 5/4, &tmp);
	int fullMoonMarchWeekday = ((int)tmp + fullMoonMarchDay - 10 - s) % 7;

	int easterMarchDay = fullMoonMarchDay - fullMoonMarchWeekday + 7;

	struct tm easter = {
		.tm_sec = 0,
		.tm_min = 0,
		.tm_hour = 0,
		.tm_mday = 0,
		.tm_mon = 0,
		.tm_year = year - 1900,
		.tm_isdst = 0
	};

	if(easterMarchDay <= 31){
		easter.tm_mday = easterMarchDay;
		easter.tm_mon = 2;
	}
	else{
		easterMarchDay -= 31;
		easter.tm_mday = easterMarchDay;
		easter.tm_mon = 3;
	}

	return easter;
}

/**
 * @brief get easter day as struct tm. Based on carter's algorithm
 * @param year: the year of reference. Must be between 1900 and 2099
 */
struct tm easterDate19002099(int year){
	
	if(
		year < 1900 ||
		year > 2099
	){
		errno = EDOM;
		struct tm ret = {0};
		return ret;
	}

	int fullMoonFromMarch21 = 204 - 11*(year % 19);
	int fullMoonMarchDay = fullMoonFromMarch21 % 30 + 21;

	if(fullMoonMarchDay > 48){
		fullMoonMarchDay--;
	}

	double tmp;
	modf((float)year * 5/4, &tmp);

	int fullMoonMarchWeekday = ((int)tmp + fullMoonMarchDay - 13) % 7;
	int easterMarchDay = fullMoonMarchDay - fullMoonMarchWeekday + 7;

	struct tm easterTm = {
		.tm_sec = 0,
		.tm_min = 0,
		.tm_hour = 0,
		.tm_mday = 0,
		.tm_mon = 0,
		.tm_year = year - 1900,
		.tm_isdst = 0
	};

	if(easterMarchDay <= 31){
		easterTm.tm_mday = easterMarchDay;
		easterTm.tm_mon = 2;
	}
	else{
		easterTm.tm_mday = easterMarchDay - 31;
		easterTm.tm_mon = 3;
	}

	return easterTm;
}

#endif