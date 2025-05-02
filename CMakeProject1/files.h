#pragma once
#include "todolist.h"

void xor_encrypt_decrypt(char* data, char key);

int save_to_file(todo* list);

todo* read_from_file();