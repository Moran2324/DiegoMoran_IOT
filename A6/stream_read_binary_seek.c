#include <stdio.h>
#include <stdlib.h>

#define LEN 32
#define ELEMENTS 3

typedef struct {
    int id;
    float data;
    char name[LEN];
} sAnalogData_t;

sAnalogData_t aData[ELEMENTS] = {
    { 0, 3.1416, "Temperature" },
    { 1, 1.18, "Humidity" },
    { 2, 23.5, "Pressure" }
};

void fwrite_test() {
    FILE *fout = fopen("AnalogData.bin", "wb");
    if (fout == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    fwrite((void *)aData, sizeof(sAnalogData_t), ELEMENTS, fout);
    fclose(fout);
}

int main() {
    fwrite_test();
    return 0;
}
