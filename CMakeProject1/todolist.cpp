#include "todolist.h"


void sort(todo* lista)
{
	bool swap = false;
	for (int i = 0; i < lista->zadania_size - 1; i++) {
		swap = false;
		for (int j = 0; j < lista->zadania_size - i - 1; j++) {
			int days1 = how_many_days_until(lista->zadania[j].deadline);
			int days2 = how_many_days_until(lista->zadania[j + 1].deadline);
			if (days1 > days2) {
				swap = true;
				task tmp = create_task(lista->zadania[j].name, lista->zadania[j].deadline);
				lista->zadania[j] = lista->zadania[j + 1];
				lista->zadania[j + 1] = tmp;
			}
		}
		if (swap == false) {
			return;
		}
	}
}

void add_task(todo* lista, task* zadanie)
{
	lista->zadania[lista->zadania_size] = *zadanie;
	lista->zadania_size++;
	sort(lista);
}

void rm_task(todo* lista, int index)
{
	if (lista->zadania_size > 0 && (index >= 0 && index < lista->zadania_size)) {
		free((char*)lista->zadania[index].name);
		free((char*)lista->zadania[index].deadline);
		for (int i = index; i < lista->zadania_size - 1; i++) {
			lista->zadania[i] = lista->zadania[i + 1];
		}
		lista->zadania_size--;
	}
}

task create_task(char* name, date* deadline)
{
	task zadanie;
	zadanie.name = (char*)malloc(strlen(name) + 1);
	if (zadanie.name != NULL) {
		strcpy((char*)zadanie.name, name);
	}
	if (deadline != NULL) {
		zadanie.deadline = (date*)malloc(sizeof(date));
		if (zadanie.deadline != NULL) {
			zadanie.deadline = create_date(deadline->day, deadline->month, deadline->year);
		}
	}
	return zadanie;
}

void clean_memory(todo* lista) {
	for (int i = 0; i < lista->zadania_size; i++) {
		free((char*)lista->zadania[i].name);
		free((char*)lista->zadania[i].deadline);
	}
	free(lista->zadania);
}



void test(todo lista) {
	printf("TEST\n");
	for (int i = 0; i < lista.zadania_size; i++) {
		printf("%s    ", lista.zadania[i].name);
		print_date(lista.zadania[i].deadline);
		printf("\n");
	}
}