#include "date.h"

int is_leap_year(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int days_in_month(int month, int year)
{
	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
		return 30;
	case 2:
		return is_leap_year(year) ? 29 : 28;
	default:
		return 0;
	}
}

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
	if (s == NULL)
		return NULL;
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

char* print_date(date* d)
{
	if (d == NULL) return NULL;
	char* buffer = (char*)malloc(11);
	if (buffer != NULL) {
		sprintf(buffer, "%02d.%02d.%04d", d->day, d->month, d->year);
	}
	return buffer;
}

date* validate_date(date* data, char* str)
{
	data = string_2_date(str);
	if (data == NULL)
		return NULL;

	if (data->year < 1 || data->month < 1 || data->month > 12)
		return NULL;

	int max_day = days_in_month(data->month, data->year);
	if (data->day < 1 || data->day > max_day)
		return NULL;

	return data;
}

bool compare_dates(date* d1, date* d2)
{
	if (d1->day == d2->day && d1->month == d2->month && d1->year == d2->year) {
		return true;
	}
	return false;
}
