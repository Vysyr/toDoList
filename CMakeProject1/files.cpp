#include "files.h"

void xor_encrypt_decrypt(char* data, char key)
{
    int i = 0;
    while (data[i] != '\0') {
        data[i] ^= key;
        i++;
    }
}

int save_to_file(todo* list)
{
    //otwieramy plik w trybie zapisu (nadpisujemy)
    FILE* file = fopen("data.txt", "w");

    if (file == NULL) {
        printf("B³¹d otwierania pliku!\n");
        return -1;
    }
    char temp[4096] = { 0 }; 
    for (int i = 0; i < list->zadania_size; i++) {
        char line[128];
        sprintf(line, "%s/%d.%d.%d,", list->zadania[i].name,
            list->zadania[i].deadline->day,
            list->zadania[i].deadline->month,
            list->zadania[i].deadline->year);
        strcat(temp, line);
    }

    // Szyfruj
    xor_encrypt_decrypt(temp, 0xAA);

    fwrite(temp, 1, strlen(temp), file);
    fclose(file);

    fclose(file);
    return 0;
}

todo* read_from_file()
{
    FILE* file = fopen("data.txt", "rb");
    if (!file) {
        perror("Nie mo¿na otworzyæ pliku z danymi");
        return NULL;
    }

    //ustalamy wielkosc pliku
    fseek(file, 0, SEEK_END); //przesuwa kursor do konca
    long length = ftell(file); //zwraca pozycje kursora (jest na koncu wiec zwroci wielkosc pliku)
    rewind(file); //kursor wraca na poczatek

    //bufor na wszystkie dane
    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        perror("Plik z danymi jest za du¿y\n");
        fclose(file);
        return NULL;
    }

    //czytamy wszytsko
    fread(buffer, 1, length, file);
    buffer[length] = '\0';  //dodajemy koniec stringa
    xor_encrypt_decrypt(buffer, 0xAA);
    fclose(file);
    
    //parsowanie bufora do listy zadan
    todo* lista = (todo*)malloc(sizeof(todo));
    lista->zadania_size = 0;
    lista->zadania = (task*)malloc(sizeof(task) * 100);

    char* token = strtok(buffer, ","); //zastepuje pierwszy taki znak \0
    while (token != NULL) {
        char* slash = strchr(token, '/'); //znajduje taki znak
        if (slash != NULL) {
            *slash = '\0'; //rozdzielamy stringa
            char* name = token; // nazwa zadania
            char* date_str = slash + 1; //deadline zadania

            //walidujemy stringa z data i dodajemy zadanie do listy
            date* deadline = validate_date(NULL, date_str);
            if (deadline != NULL) {
                task new_task = create_task(name, deadline);
                add_task(lista, &new_task);
            }
        }

        token = strtok(NULL, ","); // szuka dalej null -> kontytuuje na poprzednim stringu
    }

    free(buffer);
    return lista;
}
