#ifndef PRODUTO_H
#define PRODUTO_H

#include "categoria.h"

#define CAPACIDADE 50

typedef struct {
    int codigo;
    char nome[50];
    char prateleira;
    float preco;
    int quantidade;
    int disponivel;
    int codigoCategoria;
} Produto;

void exibirProduto(Produto prod, Categoria categorias[], int totalCat);
int buscarPorCodigo(Produto lista[], int total, int codigo);
int buscarPorNome(Produto lista[], int total, const char *nome);
int cadastrarProduto(Produto lista[], int total, Categoria categorias[], int totalCat);
void listarProdutos(Produto lista[], int total, Categoria categorias[], int totalCat);
void pesquisarProduto(Produto lista[], int total, Categoria categorias[], int totalCat);
void salvarProdutosArquivo(Produto lista[], int total);
int carregarProdutosArquivo(Produto lista[]);

#endif