//EXECUTAR
//.\main.exe

//Dicionário
//Funções Nativas do C:
// scanf = scan formatted, função que lê dados do teclado e  salva em uma variável.
// fgets = file get string ,função que lê uma linha de texto do teclado e salva em uma variável do tipo string.

//Especificadores:
// %d = inteiro decimal

//CÓDIGO 11
#include <stdio.h>
#include "produto.h"
#include "categoria.h"
#include "util.h"

int main(void) {
    int opcao = 0;
    int opcaoCat = 0;

    Categoria listaCategorias[CAPACIDADE_CATEGORIAS];
    int totalCategorias = 0;

    Produto listaProdutos[CAPACIDADE];
    int totalProdutos = 0;

    totalCategorias = carregarCategoriasArquivo(listaCategorias);
    totalProdutos = carregarProdutosArquivo(listaProdutos);

    do {
        printf("\n====================================\n");
        printf("       SISTEMA DE ESTOQUE - MENU    \n");
        printf("====================================\n");
        printf("1 - Cadastrar Produto\n");
        printf("2 - Listar Produtos\n");
        printf("3 - Pesquisar Produto\n");
        printf("4 - Alterar Estoque de um Produto\n");
        printf("5 - Remover Produto\n");
        printf("6 - Categorias\n");
        printf("7 - Sair\n");
        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                totalProdutos = cadastrarProduto(listaProdutos, totalProdutos, listaCategorias, totalCategorias);
                salvarProdutosArquivo(listaProdutos, totalProdutos);
                break;
            case 2:
                listarProdutos(listaProdutos, totalProdutos, listaCategorias, totalCategorias);
                break;
            case 3:
                pesquisarProduto(listaProdutos, totalProdutos, listaCategorias, totalCategorias);
                break;
            case 4:
                alterarEstoque(listaProdutos, totalProdutos, listaCategorias, totalCategorias);
                salvarProdutosArquivo(listaProdutos, totalProdutos);
                break;
            case 5:
                removerProduto(listaProdutos, totalProdutos);
                salvarProdutosArquivo(listaProdutos, totalProdutos);
                break;
            case 6:
                do {
                    printf("\n------------------------------------\n");
                    printf("       SUBMENU - CATEGORIAS         \n");
                    printf("------------------------------------\n");
                    printf("1 - Cadastrar Categoria\n");
                    printf("2 - Listar Categorias\n");
                    printf("3 - Voltar\n");
                    opcaoCat = lerInteiro("Escolha uma opcao: ");

                    switch (opcaoCat) {
                        case 1:
                            totalCategorias = cadastrarCategoria(listaCategorias, totalCategorias);
                            salvarCategoriasArquivo(listaCategorias, totalCategorias);
                            break;
                        case 2:
                            listarCategorias(listaCategorias, totalCategorias);
                            break;
                        case 3:
                            printf("\nVoltando ao menu principal...\n");
                            break;
                        default:
                            printf("\n[ERRO] Opcao invalida! Escolha entre 1 e 3.\n");
                            break;
                    }
                } while (opcaoCat != 3);
                break;
            case 7:
                salvarCategoriasArquivo(listaCategorias, totalCategorias);
                salvarProdutosArquivo(listaProdutos, totalProdutos);
                printf("\nDados salvos com sucesso. Saindo do sistema...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida! Escolha entre 1 e 7.\n");
                break;
        }
    } while (opcao != 7);

    return 0;
}
