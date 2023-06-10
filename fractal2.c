//Preenchimento de espaço de Hilbert (número de matrícula par)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define MAX_ITERACAO 4
#define MAX_STRING_TAM 65000

void iteraString(const char *origem, char *destino, const char *regraX, const char *regraY);

int main() {
    double angulo = 90.0 * M_PI / 180.0; // ângulo de rotação em radianos
    const char *axioma = "X";
    const char *regraX = "-YF+XFX+FY-";
    const char *regraY = "+XF-YFY-FX+";
    char string[MAX_STRING_TAM];

    FILE *file = fopen("hilbert_fractal.txt", "w");
    if (file == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    strcpy(string, axioma);

    fprintf(file, "Quantidade de estágios: %d\n", MAX_ITERACAO);
    fprintf(file, "Axioma: %s\n", axioma);
    fprintf(file, "Ângulo de rotação: %f\n", angulo);
    fprintf(file, "Regra X: %s\n", regraX);
    fprintf(file, "Regra Y: %s\n\n", regraY);

    for(int i = 1; i <= MAX_ITERACAO; i++){
        iteraString(string, string, regraX, regraY);
        printf("Estágio %d: %s\n\n", i, string);
        fprintf(file, "Estágio %d: %s\n\n", i, string);
    }

    fclose(file);
    printf("Fractal gerado e gravado em 'hilbert_fractal.txt'.\n");

    return 0;
}

void iteraString(const char *origem, char *destino, const char *regraX, const char *regraY){
    strcpy(destino, origem);
    char *stringTemp = (char *)malloc(sizeof(char) * MAX_STRING_TAM);

    int tamanho = strlen(destino);
    int index = 0;

    for (int i = 0; i < tamanho; i++){
        char charAtual = destino[i];

        if(charAtual == 'X'){
            // aplicar a regra X
            strcpy(stringTemp + index, regraX);
            index += strlen(regraX);
        } else if (charAtual == 'Y'){
            // aplicar a regra Y
            strcpy(stringTemp + index, regraY);
            index += strlen(regraY);
        } else {
            // manter os caracteres que não são regras
            stringTemp[index++] = charAtual;
        }
    }

    strcpy(destino, stringTemp);
    free(stringTemp);
}


