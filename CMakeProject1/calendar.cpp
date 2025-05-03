#include "calendar.h"

void print_month(int mnum)
{
	switch (mnum) {
	case 1:
		printf("January");
		break;
    case 2:
        printf("February");
        break;
    case 3:
        printf("March");
        break;
    case 4:
        printf("April");
        break;
    case 5:
        printf("May");
        break;
    case 6:
        printf("June");
        break;
    case 7:
        printf("July");
        break;
    case 8:
        printf("August");
        break;
    case 9:
        printf("September");
        break;
    case 10:
        printf("October");
        break;
    case 11:
        printf("November");
        break;
    case 12:
        printf("December");
        break;
	}
}

void print_weekday(date* d)
{
    const char* days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    struct tm time_info = { 0 };

    time_info.tm_year = d->year - 1900;
    time_info.tm_mon = d->month - 1;
    time_info.tm_mday = d->day;
    mktime(&time_info);
    printf("%s", days[time_info.tm_wday]);
}

void print_calendar(todo* list)
{
	system("cls");
	date* today = get_today_date();
    print_month(today->month);
    int n_days = days_in_month(today->month, today->year);
    for (int i = 1; i <= n_days; i++) {
        date* d = create_date(i, today->month, today->year);
        printf("\n%d.", i);
        print_weekday(d);
        printf("\n");
        for (int j = 0; j < list->zadania_size; j++) {
            if (compare_dates(d, list->zadania[j].deadline)) {
                printf("%s\n", list->zadania[j].name);
            }
        }
    }
    today->month ++;
    if (today->month > 12) {
        today->month = 1;
        today->year++;
    }
    if (today->day > days_in_month(today->month, today->year)) {
        today->day = days_in_month(today->month, today->year);
    }
    printf("\n\n\n");
    print_month(today->month);
    printf("\n");
    n_days = days_in_month(today->month, today->year);
    for (int i = 1; i <= n_days; i++) {
        date* d = create_date(i, today->month, today->year);
        printf("\n%d.", i);
        print_weekday(d);
        printf("\n");
        for (int j = 0; j < list->zadania_size; j++) {
            if (compare_dates(d, list->zadania[j].deadline)) {
                printf("%s\n", list->zadania[j].name);
            }
        }
    }

	printf("\n\n");
	system("pause");
}
