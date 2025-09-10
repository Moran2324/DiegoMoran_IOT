#include <stdio.h>
#include <stdlib.h>

#define LEN 32
#define ELEMENTS 3

typedef struct {
    int id;
    float data;
    char name[LEN];
} sAnalogData_t;

void fread_test() {
    FILE *fin = fopen("AnalogData.bin", "rb");
    if (fin == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    sAnalogData_t temp;

    // Leer en orden inverso
    for (int i = ELEMENTS - 1; i >= 0; i--) {
        fseek(fin, i * sizeof(sAnalogData_t), SEEK_SET);
        fread(&temp, sizeof(sAnalogData_t), 1, fin);
        printf("ID: %d, Data: %.2f, Name: %s\n", temp.id, temp.data, temp.name);
    }

    fclose(fin);
}

int main() {
    fread_test();
    return 0;
}
