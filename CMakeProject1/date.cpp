#include "date.h"

date* create_date(int d, int m, int y)
{
	date* dat = (date*)malloc(sizeof(date));
	dat->day = d;
	dat->month = m;
	dat->year = y;

	return dat;
}

date* string_2_date(char* s)
{
	int d, m, y;
	// Spróbuj sparsować datę w formacie "DD-MM-YYYY" lub "DD/MM/YYYY"
	if (sscanf(s, "%d-%d-%d", &d, &m, &y) != 3 &&
		sscanf(s, "%d/%d/%d", &d, &m, &y) != 3 &&
		sscanf(s, "%d.%d.%d", &d, &m, &y) != 3)
	{
		return NULL; // Zwróć NULL, jeśli nie udało się sparsować
	}

	return create_date(d, m, y);
}

date* get_today_date()
{
	time_t t = time(NULL);
	struct tm* tm_info = localtime(&t);

	int day = tm_info->tm_mday;
	int month = tm_info->tm_mon + 1;
	int year = tm_info->tm_year + 1900;

	return create_date(day, month, year);
}

int how_many_days_until(date* d)
{
	if (d == NULL) return 0;

	//today
	time_t now = time(NULL);
	struct tm today_tm = *localtime(&now);

	//target date
	struct tm target_tm = { 0 };
	target_tm.tm_mday = d->day;
	target_tm.tm_mon = d->month - 1;
	target_tm.tm_year = d->year - 1900;

	//diff in seconds -> days
	time_t today_time = mktime(&today_tm);
	time_t target_time = mktime(&target_tm);
	double diff_sec = difftime(target_time, today_time);
	int days = (int)(diff_sec / (60 * 60 * 24));

	return days;
}

void print_date(date* d)
{
	printf("%d.%d.%d", d->day, d->month, d->year);
}
