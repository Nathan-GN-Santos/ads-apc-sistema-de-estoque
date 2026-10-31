#ifndef UTIL_H
#define UTIL_H

void limparBuffer(void);

// Repetem até o usuário digitar algo do tipo certo
int   lerInteiro(const char *mensagem);
float lerFloat(const char *mensagem);
char  lerCaractere(const char *mensagem);
void  lerTexto(const char *mensagem, char *destino, int tamanho);

// Validações genéricas (retornam 1 se válido, 0 se inválido)
int ehPositivoInt(int valor);
int ehPositivoFloat(float valor);
int ehNaoNegativo(int valor);
int textoPreenchido(const char *texto);

#endif