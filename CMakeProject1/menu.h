#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "todolist.h"
#include "date.h"
#include "files.h"

void print_list(todo* list);

bool handle_selection(todo* list, int sel);

void task_creator(todo* list);

void menu();