#include <stdio.h>
#include <string.h>
#include "categoria.h"
#include "util.h"

void exibirCategoria(Categoria cat) {
    printf("\n------------------------------------\n");
    printf("Codigo da Categoria: %d\n", cat.codigo);
    printf("Nome da Categoria:   %s\n", cat.nome);
    printf("------------------------------------\n");
}

int buscarCategoriaPorCodigo(Categoria lista[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (lista[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int buscarCategoriaPorNome(Categoria lista[], int total, const char *nome) {
    for (int i = 0; i < total; i++) {
        if (strcmp(lista[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

int cadastrarCategoria(Categoria lista[], int total) {
    if (total >= CAPACIDADE_CATEGORIAS) {
      	printf("\n[ERRO] A lista de categorias esta cheia (limite de %d)!\n", CAPACIDADE_CATEGORIAS);
        return total;
    }

    Categoria cat;
    printf("\n--- CADASTRO DE CATEGORIA ---\n");

    // ValidaÃ§Ã£o do CÃ³digo da Categoria
    do {
        cat.codigo = lerInteiro("Digite o Codigo da categoria (inteiro positivo): ");
        if (!ehPositivoInt(cat.codigo)) {
            printf("[ERRO] Codigo invalido! Deve ser maior que zero.\n");
        } else if (buscarCategoriaPorCodigo(lista, total, cat.codigo) != -1) {
            printf("[ERRO] Codigo de categoria ja cadastrado!\n");
        }
    } while (!ehPositivoInt(cat.codigo) || buscarCategoriaPorCodigo(lista, total, cat.codigo) != -1);

    // Validação do Nome usando lerTexto e textoPreenchido
    do {
        lerTexto("Digite o Nome da categoria: ", cat.nome, sizeof(cat.nome));
        if (!textoPreenchido(cat.nome)) {
            printf("[ERRO] O nome da categoria nao pode ficar em branco!\n");
        }
    } while (!textoPreenchido(cat.nome));

    lista[total] = cat;
    printf("\n[SUCESSO] Categoria cadastrada com sucesso!\n");
    exibirCategoria(cat);

    return total + 1;
}

void listarCategorias(Categoria lista[], int total) {
    if (total == 0) {
        printf("\n[AVISO] Nenhuma categoria cadastrada.\n");
        return;
    }

    printf("\n=== LISTA DE CATEGORIAS ===\n");
    for (int i = 0; i < total; i++) {
        exibirCategoria(lista[i]);
    }
}

// PersistÃªncia: Salvar categorias em arquivo de texto
void salvarCategoriasArquivo(Categoria lista[], int total) {
    FILE *file = fopen("categorias.txt", "w");
    if (file == NULL) {
        return;
    }
    fprintf(file, "%d\n", total);
    for (int i = 0; i < total; i++) {
        fprintf(file, "%d\n%s\n", lista[i].codigo, lista[i].nome);
    }
    fclose(file);
}

// Persistência: Carregar categorias do arquivo de texto
int carregarCategoriasArquivo(Categoria lista[]) {
    FILE *file = fopen("categorias.txt", "r");
    if (file == NULL) return 0;

    int total = 0;
    if (fscanf(file, "%d", &total) != 1 || total < 0) {
        fclose(file);
        return 0;
    }
    if (total > CAPACIDADE_CATEGORIAS) total = CAPACIDADE_CATEGORIAS;

    int lidos = 0;
    for (int i = 0; i < total; i++) {
        Categoria c;
        if (fscanf(file, "%d", &c.codigo) != 1) break;
        fgetc(file);
        if (fgets(c.nome, sizeof(c.nome), file) == NULL) break;
        c.nome[strcspn(c.nome, "\n")] = '\0';
        lista[lidos++] = c;
    }
    fclose(file);
    return lidos;
}