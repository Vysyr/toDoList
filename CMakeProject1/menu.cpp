#include "menu.h"



void print_list(todo* list)
{
	printf("Zadania do zrobienia: %d\n\n", list->zadania_size);
	for (int i = 0; i < list->zadania_size; i++) {
		printf("%d. %s %s days left: %d\n", i + 1, list->zadania[i].name, print_date(list->zadania[i].deadline), how_many_days_until(list->zadania[i].deadline));
	}
}

bool handle_selection(todo* list, int sel)
{
	if (sel == 0) {
		//kreator nowego zadania
		task_creator(list);
	}
	else if (sel > 0 && sel <= list->zadania_size) {
		// usuwanie zadania o indeksie sel-1
		rm_task(list, sel - 1);
	}
	else if (sel == -1) {
		// wyjscie
		return true;
	}
	else if (sel == -10) {
		print_calendar(list);
	}
	return false;
}


void task_creator(todo* list)
{
	system("cls");
	char nazwa[100];
	char data[11];
	date* deadline = NULL;
	task* t = NULL;
	printf("Task name: ");
	getchar(); //ignoruje \n poprzedni
	fgets(nazwa, sizeof(nazwa), stdin); // zapisuje cala linie razem z \n
	//wyczyszczenie inputu z niepozadanych znakow
	for (int i = 0; i < sizeof(nazwa); i++) {
		if (nazwa[i] == '\n' || nazwa[i] == ',' || nazwa[i] == '/') {
			nazwa[i] = ' ';
		}
	}
	
	do {
		printf("Deadline (dd-mm-yyyy): ");
		scanf("%10s", data);

		deadline = validate_date(deadline, data);

		if (deadline == NULL) {
			printf("Niepoprawna data, spróbuj ponownie.\n");
		}
	} while (deadline == NULL);
	t = (task*)malloc(sizeof(task));
	if (t != NULL) {
		*t = create_task(nazwa, deadline);
		add_task(list, t);
	}
}



void menu() {
	bool quit = false;
	//wczytanie z pliku i deszyfrowanie
	todo* list = read_from_file();
	//jesli plik nie istnieje lub jest uszkodzony
	if (list == NULL) {
		list = (todo*)malloc(sizeof(todo));
		list->zadania = (task*)malloc(sizeof(task) * 100);
		list->zadania_size = 0;
	}
		//glowna petla programu
	int select = 0;
	while (!quit) {
		system("cls");
		printf(" -10 calendar view\n -1  exit\n 0 add task\n 1+ delete task\n\n");
		print_list(list);
		printf("Selection: ");
		scanf("%d", &select);
		quit = handle_selection(list, select);
	}
	//zapis do pliku i szyfrowanie
	save_to_file(list);
	clean_memory(list);
}
