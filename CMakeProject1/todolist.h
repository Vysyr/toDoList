#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date.h"

struct task {
	char* name;
	date* deadline;
};

struct todo {
	task* zadania = (task*)malloc(sizeof(task) * 100);
	int zadania_size = 0;
};

void sort(todo* lista);

void add_task(todo* lista, task* zadanie);

void rm_task(todo* lista, int index);

task create_task(char* name, date* deadline);

void test(todo lista);

void clean_memory(todo* lista);