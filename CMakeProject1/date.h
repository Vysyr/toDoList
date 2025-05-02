#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct date {
	int day;
	int month;
	int year;
};

date* create_date(int d, int m, int y);

date* string_2_date(char* s);

date* get_today_date();

int how_many_days_until(date* d);

void print_date(date* d);

