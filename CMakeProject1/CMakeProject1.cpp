// CMakeProject1.cpp: definiuje punkt wejścia dla aplikacji.
//

#include "CMakeProject1.h"

int main()
{
	todo list;
	char nazwa[100];
	date *data, *data2;
	data = get_today_date();
	data2 = string_2_date((char*)"02.06.2025");
	printf("Nazwa zadania1: ");
	scanf("%99s", &nazwa);
	task zadanie1 = create_task(nazwa, data);
	printf("Nazwa zadania2: ");
	scanf("%99s", &nazwa);
	task zadanie2 = create_task(nazwa, data2);
	printf("Nazwa zadania3: ");
	scanf("%99s", &nazwa);
	task zadanie3 = create_task(nazwa, data2);
	add_task(&list, &zadanie1);
	add_task(&list, &zadanie2);
	add_task(&list, &zadanie3);
	test(list);
	rm_task(&list, 1);
	test(list);

	clean_memory(&list);

	//date* data;
	//data = create_date(7,12,2025);
	//print_date(data); printf("\n");
	//data = string_2_date((char*)"1.5.2025");
	//print_date(data);printf("\n");
	//data = get_today_date();
	//print_date(data);printf("\n");
	//data = create_date(2, 10, 2025);
	//int days = how_many_days_until(data);
	//printf("Days until 02.10.2025: %d", days);
	return 0;
}
