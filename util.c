#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int lerInteiro(const char *mensagem) {
    int valor, r;
    printf("%s", mensagem);
    while ((r = scanf("%d", &valor)) != 1) {
        if (r == EOF) exit(1);          // entrada fechada: evita laço infinito
        limparBuffer();
        printf("[ERRO] Digite um numero inteiro valido.\n%s", mensagem);
    }
    limparBuffer();
    return valor;
}

float lerFloat(const char *mensagem) {
    float valor;
    int r;
    printf("%s", mensagem);
    while ((r = scanf("%f", &valor)) != 1) {
        if (r == EOF) exit(1);
        limparBuffer();
        printf("[ERRO] Digite um numero valido (use . para centavos).\n%s", mensagem);
    }
    limparBuffer();
    return valor;
}

char lerCaractere(const char *mensagem) {
    char c;
    printf("%s", mensagem);
    if (scanf(" %c", &c) != 1) exit(1);
    limparBuffer();
    return c;
}

void lerTexto(const char *mensagem, char *destino, int tamanho) {
    printf("%s", mensagem);
    if (fgets(destino, tamanho, stdin) == NULL) {
        destino[0] = '\0';
        return;
    }
    size_t pos = strcspn(destino, "\n");
    if (destino[pos] == '\n') {
        destino[pos] = '\0';
    } else {
        limparBuffer();   // texto maior que o buffer: descarta o excedente
    }
}

int ehPositivoInt(int valor)     { return valor > 0; }
int ehPositivoFloat(float valor) { return valor > 0.0f; }
int ehNaoNegativo(int valor)     { return valor >= 0; }
int textoPreenchido(const char *texto) { return strlen(texto) > 0; }