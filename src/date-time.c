#include <stdio.h>

#include "date-time.h"
#include "constants.h"
#include "maths.h"
#include "memory.h"
#include "types.h"


#define DAYS_IN_JANUARY 31
#define DAYS_IN_FEBRUARY 28
#define DAYS_IN_MARCH 31
#define DAYS_IN_APRIL 30
#define DAYS_IN_MAY 31
#define DAYS_IN_JUNE 30
#define DAYS_IN_JULY 31
#define DAYS_IN_AUGUST 31
#define DAYS_IN_SEPTEMBER 30
#define DAYS_IN_OCTOBER 31
#define DAYS_IN_NOVEMBER 30
#define DAYS_IN_DECEMBER 31

#define DAYS_BEFORE_FEBRUARY DAYS_IN_JANUARY
#define DAYS_BEFORE_MARCH (DAYS_IN_FEBRUARY + DAYS_BEFORE_FEBRUARY)
#define DAYS_BEFORE_APRIL (DAYS_IN_MARCH + DAYS_BEFORE_MARCH)
#define DAYS_BEFORE_MAY (DAYS_IN_APRIL + DAYS_BEFORE_APRIL)
#define DAYS_BEFORE_JUNE (DAYS_IN_MAY + DAYS_BEFORE_MAY)
#define DAYS_BEFORE_JULY (DAYS_IN_JUNE + DAYS_BEFORE_JUNE)
#define DAYS_BEFORE_AUGUST (DAYS_IN_JULY + DAYS_BEFORE_JULY)
#define DAYS_BEFORE_SEPTEMBER (DAYS_IN_AUGUST + DAYS_BEFORE_AUGUST)
#define DAYS_BEFORE_OCTOBER (DAYS_IN_SEPTEMBER + DAYS_BEFORE_SEPTEMBER)
#define DAYS_BEFORE_NOVEMBER (DAYS_IN_OCTOBER + DAYS_BEFORE_OCTOBER)
#define DAYS_BEFORE_DECEMBER (DAYS_IN_NOVEMBER + DAYS_BEFORE_NOVEMBER)


Date getDate(const int fd) {
	u8 bytes[4];
	readFromMemory(fd, POINTER_TO_CURRENT_DATETIME, 4, bytes);

	const u8 yearBytes[2] = {bytes[2], bytes[3]};
	const u16 year = hexBytesToInt(yearBytes, 2);

	u16 days = hexBytesToInt(bytes, 1);
	if (bytes[1] & 1) {
		days += 255;
	}

	if (days > 59) {
		const bool isLeapYear = !(year % 4) && (year % 100 || !(year % 400));
		days -= isLeapYear;
	}

	return (Date){days, year};
}

void printDateTime(const int fd) {
	Date date = getDate(fd);

	if (date.days <= DAYS_BEFORE_FEBRUARY) {
		printf("January");
	} else if (date.days <= DAYS_BEFORE_MARCH) {
		date.days -= DAYS_BEFORE_FEBRUARY;
		printf("February");
	} else if (date.days <= DAYS_BEFORE_APRIL) {
		date.days -= DAYS_BEFORE_MARCH;
		printf("March");
	} else if (date.days <= DAYS_BEFORE_MAY) {
		date.days -= DAYS_BEFORE_APRIL;
		printf("April");
	} else if (date.days <= DAYS_BEFORE_JUNE) {
		date.days -= DAYS_BEFORE_MAY;
		printf("May");
	} else if (date.days <= DAYS_BEFORE_JULY) {
		date.days -= DAYS_BEFORE_JUNE;
		printf("June");
	} else if (date.days <= DAYS_BEFORE_AUGUST) {
		date.days -= DAYS_BEFORE_JULY;
		printf("July");
	} else if (date.days <= DAYS_BEFORE_SEPTEMBER) {
		date.days -= DAYS_BEFORE_AUGUST;
		printf("August");
	} else if (date.days <= DAYS_BEFORE_OCTOBER) {
		date.days -= DAYS_BEFORE_SEPTEMBER;
		printf("September");
	} else if (date.days <= DAYS_BEFORE_NOVEMBER) {
		date.days -= DAYS_BEFORE_OCTOBER;
		printf("October");
	} else if (date.days <= DAYS_BEFORE_DECEMBER) {
		date.days -= DAYS_BEFORE_NOVEMBER;
		printf("November");
	} else {
		date.days -= DAYS_BEFORE_DECEMBER;
		printf("December");
	}

	printf(" %d, %d\n", date.days, date.year);
}
