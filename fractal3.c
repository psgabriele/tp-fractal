//Fractal definido por mim

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define MAX_ITERACAO 4
#define MAX_STRING_TAM 65536

void iteraString(const char *origem, char *destino, const char *regraA, const char *regraB);

int main() {
    double angulo = 90.0 * M_PI / 180.0; // ângulo de rotação em radianos
    const char *axioma = "A";
    const char *regraA = "FB+FB+FB+FB";
    const char *regraB = "-AF+BF+FB-FA";
    char string[MAX_STRING_TAM];

    FILE *file = fopen("meu_fractal.txt", "w");
    if (file == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    strcpy(string, axioma);

    fprintf(file, "Quantidade de estágios: %d\n", MAX_ITERACAO);
    fprintf(file, "Axioma: %s\n", axioma);
    fprintf(file, "Ângulo de rotação: %f\n", angulo);
    fprintf(file, "Regra A: %s\n", regraA);
    fprintf(file, "Regra B: %s\n\n", regraB);

    for(int i = 1; i <= MAX_ITERACAO; i++){
        iteraString(string, string, regraA, regraB);
        printf("Estágio %d: %s\n\n", i, string);
        fprintf(file, "Estágio %d: %s\n\n", i, string);
    }

    fclose(file);
    printf("Fractal gerado e gravado em 'meu_fractal.txt'.\n");

    return 0;
}

void iteraString(const char *origem, char *destino, const char *regraA, const char *regraB){
    strcpy(destino, origem);
    char *stringTemp = (char *)malloc(sizeof(char) * MAX_STRING_TAM);

    int tamanho = strlen(destino);
    int index = 0;

    for (int i = 0; i < tamanho; i++){
        char charAtual = destino[i];

        if(charAtual == 'A'){
            // aplicar a regra A
            strcpy(stringTemp + index, regraA);
            index += strlen(regraA);
        } else if (charAtual == 'B'){
            // aplicar a regra B
            strcpy(stringTemp + index, regraB);
            index += strlen(regraB);
        } else {
            // manter os caracteres que não são regras
            stringTemp[index++] = charAtual;
        }
    }

    strcpy(destino, stringTemp);
    free(stringTemp);
}