/*
• Floco de neve onda senoidal 1 de von Koch (somatório dos algarismos do número de matrícula mod 4 = 1)
-> número de matrícula: 2022091544 -> soma dos algarismos: 29 -> 29 mod 4 = 1
*/

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>

#define MAX_ITERACAO 4
#define MAX_STRING_TAM 65000

void geraFractal(FILE *file, char *string, int iteracao, double angulo, const char *axioma, const char *regra);
void iteraString(FILE *file, const char *origem, char *destino, const char *regra);

int main() {
    double angulo = 60.0 * M_PI / 180.0; // ângulo de rotação em radianos
    const char *axioma = "F";
    const char *regra = "F-F++FF--F+F";
    char string[MAX_STRING_TAM];

    FILE *file = fopen("von_koch_senoidal_1.txt", "w");
    if(file == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    strcpy(string, axioma);

    fprintf(file, "Quantidade de estágios: %d\n", MAX_ITERACAO);
    fprintf(file, "Axioma: %s\n", axioma);
    fprintf(file, "Ângulo de rotação: %f\n", angulo);
    fprintf(file, "Regra: %s\n\n", regra);
  
    for (int i = 1; i <= MAX_ITERACAO; i++) {
        iteraString(file, string, string, regra);
        printf("Estágio %d: %s\n\n", i, string);
        fprintf(file, "Estágio %d: %s\n\n", i, string);
    }

    fclose(file);
    printf("Fractal gerado e gravado em 'von_koch_senoidal_1.txt'.\n");

    return 0;
}

void geraFractal(FILE *file, char *string, int iteracao, double angulo, const char *axioma, const char *regra) {
    if (iteracao == 0) {
        strcpy(string, axioma);
        return;
    }
    
    char *stringTemp = (char *)malloc(sizeof(char) * MAX_STRING_TAM);
    geraFractal(file, stringTemp, iteracao - 1, angulo, axioma, regra);

    int tamanho = strlen(stringTemp);
    int index = 0;

    for(int i = 0; i < tamanho; i++){
        char charAtual = stringTemp[i];

        if(charAtual == '+'){
            string[index++] = '+';
        } else if(charAtual == '-'){
            string[index++] = '-';
        } else if(charAtual == 'F'){
            string[index++] = 'F';
            string[index++] = '-';
            string[index++] = 'F';
            string[index++] = '+';
            string[index++] = '+';
            string[index++] = 'F';
            string[index++] = 'F';
            string[index++] = '-';
            string[index++] = '-';
            string[index++] = 'F';
            string[index++] = '+';
            string[index++] = 'F';
        }
    }

    string[index] = '\0';

    free(stringTemp);
}

void iteraString(FILE *file, const char *origem, char *destino, const char *regra) {
    double angulo = 60.0 * M_PI / 180.0; // ângulo de rotação em radianos
    strcpy(destino, origem);
    geraFractal(file, destino, 1, angulo, origem, regra);
}