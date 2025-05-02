#include "todolist.h"


void add_task(todo* lista, task* zadanie)
{
	lista->zadania[lista->zadania_size] = *zadanie;
	lista->zadania_size++;
}

task create_task(char* name)
{
	task zadanie;
	zadanie.name = name;
	return zadanie;
}



void test(todo lista) {
	printf("TEST\n");
	for (int i = 0; i < lista.zadania_size; i++) {
		printf("%s\n", lista.zadania[i].name);
	}
}