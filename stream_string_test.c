#include <stdio.h>
#include <stdlib.h>

#define LEN 1024

void stream_string_test() {
    FILE *fout, *fin;
    char line[LEN + 1];

    fout = fopen("test_file_string.txt", "w");
    if (fout == NULL) {
        perror("Error al abrir test_file_string.txt");
        exit(EXIT_FAILURE);
    }

    fin = fdopen(0, "r"); // Entrada estándar
    while (fgets(line, LEN, fin) != NULL) {
        fputs(line, fout);
    }

    fclose(fout);
}

int main() {
    stream_string_test();
    return 0;
}
