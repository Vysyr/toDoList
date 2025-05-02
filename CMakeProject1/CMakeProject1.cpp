// CMakeProject1.cpp: definiuje punkt wejścia dla aplikacji.
//

#include "CMakeProject1.h"

int main()
{
	todo list;
	char nazwa[100];
	scanf("%s", &nazwa);
	task zadanie1 = create_task(nazwa);
	task zadanie2 = create_task(nazwa);
	add_task(&list, &zadanie1);
	add_task(&list, &zadanie2);
	test(list);

	free(list.zadania);
	return 0;
}
