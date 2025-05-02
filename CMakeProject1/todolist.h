#pragma once
#include <stdio.h>
#include <stdlib.h>

struct task {
	const char* name;
};

struct todo {
	task* zadania = (task*)malloc(sizeof(task) * 100);
	int zadania_size = 0;
};

void add_task(todo* lista, task* zadanie);

void rm_task(int index);

task create_task(char* name);

void test(todo lista);